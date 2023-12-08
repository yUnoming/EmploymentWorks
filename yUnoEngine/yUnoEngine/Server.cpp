// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 マクロ定義	     	  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

constexpr unsigned short PORTNO = 49152;

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#pragma comment(lib, "ws2_32.lib")

#include "yUno_NetWorkManager.h"
#include "Server.h"
#include "SceneManager.h"
#include "Test.h"

#include <stdio.h>
#include <time.h>
#include <iostream>

char g_rockObject[256]{};

void Server::ReceiveThread()
{
	int			errcode;		// ＷＩＮＳＯＣＫのエラーコード
	int myAddressLength = 0;	// 送信元アドレスがセットされる変数の長さ

	while (true)
	{
		myAddressLength = sizeof(sockaddr);

		memset(m_receiveData.data, 0, sizeof(m_receiveData.data));

		int sts = recvfrom(
			m_mySocket,
			(char*)m_receiveData.data,
			sizeof(m_receiveData.data),
			0,
			(sockaddr*)&m_sendAddress,
			&myAddressLength);

		if (sts != SOCKET_ERROR)
		{
			if (strcmp(m_receiveData.data, "LoginSuccess") == 0)
			{
				std::cout << "Login Server" << std::endl;
			}
			else if (strcmp(m_receiveData.data, "ServerLogin") == 0)
			{
				printf("受信データ : %s \n", m_receiveData.data);
				printf("送信元ＩＰアドレス/ポート番号 %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));

				strcpy_s(m_sendData.data, sizeof(m_sendData.data), "LoginSuccess");
				int len = static_cast<int>(strlen(m_sendData.data));	// 送信文字列長を取得
				sts = sendto(
					m_mySocket,					// ソケット番号
					m_sendData.data,			// 送信データ
					len,						// 送信データ長
					0,							// フラグ
					(sockaddr*)&m_sendAddress,	// 送信先アドレス
					sizeof(sockaddr));			// アドレス構造体のバイトサイズ
			}
			else
			{
				printf("受信データ : %s\n", m_receiveData.data);
				printf("送信元ＩＰアドレス/ポート番号 %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));
				
				// ===== メッセージの種類によって処理を分岐 ===== //
				switch (m_receiveData.message.header.type)
				{
					// 通信開始
					case MessageType::CommunicationStart:
					{
						// ----- 通信相手をリストに格納 ----- //
						// 通信相手の情報を保存する
						CommunicationUserData comUser;
						comUser.userRank = (ServerRank)m_sendData.message.header.userRank;
						comUser.address = m_sendAddress;
						
						// リストに格納
						m_comUserList.push_back(comUser);

						// ----- 相手に通信成功を伝える ----- //
						m_sendData.message.header.type = MessageType::CommunicationSuccess;
						SendMessageData(m_sendData);
						break;
					}

					// 通信成功
					case MessageType::CommunicationSuccess:
						// 通信の開始を設定
						m_isCommunicationData = true;
						// システム通知を表示
						MessageBoxW(NULL, L"サーバーにログインしました", L"システム通知", MB_OK);
						break;
					// 通信終了
					case MessageType::CommunicationEnd:
						// 通信中のユーザー数だけループ
						for (auto it = m_comUserList.begin(); it != m_comUserList.end(); it++)
						{
							CommunicationUserData comUser = *it;
							// IPアドレスとポート番号が送信元と同じ？
							if (comUser.address.sin_addr.S_un.S_addr == m_sendAddress.sin_addr.S_un.S_addr &&
								comUser.address.sin_port == m_sendAddress.sin_port)
							{
								// リストから除外
								m_comUserList.erase(it);

								// メッセージ通知
								if (m_myServerRank == ServerRank::Owner)
									MessageBoxW(NULL, L"ユーザーがログアウトしました", L"システム通知", MB_OK);
								else if(m_myServerRank == ServerRank::User)
									MessageBoxW(NULL, L"サーバーが閉じました", L"システム通知", MB_OK);
								break;
							}
						}
						break;

					// コンポーネント更新
					case MessageType::UpdateComponent:
						// ===== コンポーネントの種類によって処理を分岐 ===== //
						// Transformコンポーネント
						if (strcmp(m_receiveData.message.body.componentType,
							"class PublicSystem::Transform") == 0)
						{
							// コンポーネント取得
							Transform* transform =
								SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->transform;
							// 各値を代入
							transform->Position = m_receiveData.message.body.transform.Position;
							transform->Rotation = m_receiveData.message.body.transform.Rotation;
							transform->Scale = m_receiveData.message.body.transform.Scale;
						}
						// Textコンポーネント
						else if (strcmp(m_receiveData.message.body.componentType,
							"class PublicSystem::Text") == 0)
						{
							// コンポーネント取得
							Text* text =
								SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->GetComponent<Text>();
							// 各値を代入
							text->text = m_receiveData.message.body.text.text;
							text->fontSize = m_receiveData.message.body.text.fontSize;
						}
						break;

					// オブジェクト選択
					case MessageType::ClickObject:
						// クリックされたオブジェクト名を代入
						strcpy_s(rockObjectName, m_receiveData.message.body.object.GetName());
						break;
				}
			}
		}
		// 通信を終了した？
		else if (!m_isCommunicationData)
		{
			// ループを抜ける
			break;
		}
	}
	return;
}

Server::~Server()
{
	// 通信を行っている？
	if (m_isCommunicationData)
		// サーバーを閉じる
		CloseServer();
}

void Server::OpenServer()
{
	// 通信を行っていない？
	if (!m_isCommunicationData)
	{
		WSADATA wsaData;	// WinSockの初期化データを格納
		WORD	verNo;		// バージョン指定
		int sts;			// WinSockが正しく初期化されたか代入

		// バージョン2.2を要求
		verNo = MAKEWORD(2, 2);

		// WinSock初期化時、エラーが発生した？
		if (WSAStartup(
			verNo,	// 要求バージョン
			&wsaData)	// WinSockデータを格納するための変数
			== SOCKET_ERROR)
		{
			int errorCode = WSAGetLastError();
			std::cout << "WSAStartup() Failed!!! ErrorCode：" << errorCode << std::endl;
			return;
		}

		// 要求したバージョンが利用できない？
		if (verNo != wsaData.wVersion)
		{
			std::cout << "要求したバージョンは利用できません" << std::endl;
			return;
		}

		// IPアドレス表示
		{
			char hostname[256];
			gethostname(hostname, 256);

			LPHOSTENT lphe;

			lphe = gethostbyname(hostname);
			if (lphe == nullptr)
			{
				printf("gethostbuname error!!\n");
			}
			else
			{
				in_addr ipadr{};
				memcpy(&ipadr.S_un.S_addr, lphe->h_addr_list[0], 4);
				printf("ipaddress : %s \n", inet_ntoa(ipadr));
			}
		}

		// ソケット生成
		m_mySocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (m_mySocket == INVALID_SOCKET)
		{
			std::cout << "ソケットの生成に失敗しました" << std::endl;
			return;
		}

		// 自身のアドレスを設定
		sockaddr_in myAddress{};	// 自身のアドレス
		myAddress.sin_port = htons(PORTNO);
		myAddress.sin_family = AF_INET;
		myAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

		std::cout << ntohs(myAddress.sin_port) << std::endl;

		// 自分のソケットにIPアドレス、ポート番号を割り当てる
		sts = bind(m_mySocket, (sockaddr*)&myAddress, sizeof(sockaddr));
		if (sts == SOCKET_ERROR)
		{
			std::cout << "ソケットへの割り当てに失敗しました" << std::endl;
			return;
		}
		// 通信の開始を設定
		m_isCommunicationData = true;
		// 地位を設定
		m_myServerRank = Owner;

		// 受信スレッド生成
		m_receiveThread = std::thread(&Server::ReceiveThread, this);

		MessageBoxW(NULL, L"サーバーを開きました", L"システム通知", MB_OK);
	}
}
 
void Server::CloseServer()
{
	// データの通信を行っている？
	if (m_isCommunicationData)
	{
		// ===== 通信終了を相手に通知 ===== //
		// 通信相手がいる？
		if (!m_comUserList.empty())
		{
			// メッセージ送信
			MessageData messageData;
			messageData.message.header.type = MessageType::CommunicationEnd;
			SendMessageData(messageData);
		}
		
		// ===== サーバークローズ処理 ===== //
		//　ソケットをクローズ時、エラーが発生した？
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode：" << errorCode << std::endl;
		}
		// 通信の終了を設定
		m_isCommunicationData = false;
		// ロック状態の解除
		ZeroMemory(rockObjectName, sizeof(rockObjectName));

		// スレッドの終了を待つ
		m_receiveThread.join();

		// WINSOCKの終了処理
		WSACleanup();

		MessageBoxW(NULL, L"サーバーを閉じました", L"システム通知", MB_OK);
	}
}

void Server::LoginServer()
{
	if (!m_isCommunicationData)
	{
		WSADATA wsaData;	// WinSockの初期化データを格納
		WORD	verNo;		// バージョン指定
		int sts;			// WinSockが正しく初期化されたか代入

		verNo = MAKEWORD(2, 2);	// 2.2を要求

		// WinSock初期化時、エラーが発生した？
		if (WSAStartup(
			verNo,		// 要求バージョン
			&wsaData)	// WinSockデータを格納するための変数
			== SOCKET_ERROR)
		{
			int errorCode = WSAGetLastError();
			std::cout << "WSAStartup() Failed!!! ErrorCode：" << errorCode << std::endl;
			return;
		}

		// 要求したバージョンが利用できない？
		if (verNo != wsaData.wVersion)
		{
			std::cout << "要求したバージョンは利用できません" << std::endl;
			return;
		}

		// ソケット生成
		m_mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		// ソケット生成時、エラーが発生した？
		if (m_mySocket == INVALID_SOCKET)
		{
			std::cout << "ソケットの生成に失敗しました" << std::endl;
			return;
		}

		printf("\n宛先IPアドレスを入力してください\n");

		char str[256];
		rewind(stdin);
		int r = scanf_s("%s", str, 250);

		// 宛先のアドレスを設定
		m_sendAddress.sin_port = htons(PORTNO);	// ポート番号（16ビット）をネットワークバイトオーダーに変更
		m_sendAddress.sin_family = AF_INET;
		// 10進表記のIPアドレスを32ビットに変換（ネットワークバイトオーダー）
		m_sendAddress.sin_addr.S_un.S_addr = inet_addr(str);

		// 地位を設定
		m_myServerRank = User;

		// スレッドが生成されていない？
		if(!m_receiveThread.joinable())
			// 受信スレッド生成
			m_receiveThread = std::thread(&Server::ReceiveThread, this);

		// 相手に通信開始通知を送る
		m_sendData.message.header.type = MessageType::CommunicationStart;
		SendMessageData(m_sendData);
	}
}

void Server::LogoutServer()
{
	// 通信を行っている？
	if (m_isCommunicationData)
	{
		// ===== 通信終了を相手に通知 ===== //
		MessageData messageData;
		messageData.message.header.type = MessageType::CommunicationEnd;
		SendMessageData(messageData);

		//　ソケットをクローズ時、エラーが発生した？
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode：" << errorCode << std::endl;
		}
		// 通信の終了を設定
		m_isCommunicationData = false;
		// ロック状態の解除
		ZeroMemory(rockObjectName, sizeof(rockObjectName));

		// スレッドの終了を待つ
		m_receiveThread.join();

		// WINSOCKの終了処理
		WSACleanup();
	}
	MessageBoxW(NULL, L"サーバーからログアウトしました", L"システム通知", MB_OK);
}

void Server::SendData()
{
	if (m_isCommunicationData)
	{
		// 送信データ作成
		printf("\n送信データを入力してください（アルファベットのみ）\n");
		rewind(stdin);
		int r = scanf_s("%[^\n]", m_sendData.data, 255);	// 改行以外を読み込む

		size_t len = strlen(m_sendData.data);		// 送信文字列長を取得

		// データの送信時、エラーが発生した？
		if (sendto(
			m_mySocket,							// ソケット番号
			m_sendData.data,					// 送信データ
			len,								// 送信データ長
			0,									// フラグ
			(sockaddr*)&m_sendAddress,			// 送信先アドレス
			sizeof(sockaddr))					// アドレス構造体のバイト長
			== SOCKET_ERROR)
		{
			std::cout << "データの送信に失敗しました" << std::endl;
		}
	}
}

void Server::SendMessageData(MessageData& messageData)
{
	if (m_isCommunicationData)
	{
		// ===== その他に送る情報を代入 ===== //
		// ユーザーランク
		messageData.message.header.userRank = m_myServerRank;

		// ===== 送信処理 ===== //
		// データの送信時、エラーが発生した？
		if (sendto(
			m_mySocket,							// ソケット番号
			messageData.data,					// 送信データ
			sizeof(messageData.data),			// 送信データ長
			0,									// フラグ
			(sockaddr*)&m_sendAddress,			// 送信先アドレス
			sizeof(sockaddr))					// アドレス構造体のバイト長
			== SOCKET_ERROR)
		{
			std::cout << "データの送信に失敗しました" << std::endl;
		}
	}
}

bool Server::IsRockObject(const char* objectName)
{
	// ロックされていない？別のオブジェクトをロックしている？
	if (rockObjectName == nullptr || strcmp(rockObjectName, objectName) != 0)
		return false;
	return true;
}
