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

#include "SystemNetWorkManager.h"
#include "SceneManager.h"
#include "TemplateCube.h"
#include "TemplateText.h"
#include "Time.h"

#include <stdio.h>
#include <time.h>
#include <iostream>

char g_rockObject[256]{};

void Ctlan::PrivateSystem::Server::ReceiveThread()
{
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
#if _DEBUG
			printf("送信元ＩＰアドレス/ポート番号 %s/%d \n",
				inet_ntoa(m_sendAddress.sin_addr),
				ntohs(m_sendAddress.sin_port));
#endif
			// ===== メッセージの種類によって処理を分岐 ===== //
			switch (m_receiveData.message.header.type)
			{
				//----------//
				// 通信開始 //
				case MessageType::CommunicationStart:
				{
					// ----- 通信相手をリストに格納 ----- //
					// 通信相手の情報を保存する
					CommunicationUserData comUser;						// 通信ユーザー情報
					comUser.userRank =									// ユーザーランク
						(ServerRank)m_sendData.message.header.userRank;
					int userNo = 1;										// ユーザー番号(１番から確認)
					bool success = true;								// ユーザー番号が決まったかどうか

					// ユーザー番号が決まるまでループ
					do
					{
						success = true;
						// 現在ログインしているユーザー分ループ
						for (const CommunicationUserData& data : m_comUserList)
						{
							// ユーザー番号が他ユーザーと被った？
							if (data.userNo == userNo)
							{
								userNo++;		// 番号を加算
								success = false;// 再度ループするように変更
								break;
							}
						}
					} while (!success);

					// 値代入
					m_sendData.message.header.userRank = User;
					m_sendData.message.header.userNo = userNo;
					comUser.userNo = userNo;
					comUser.address = m_sendAddress;
					// リストに格納
					m_comUserList.push_back(comUser);

					// ----- 相手に通信成功を伝える ----- //
					m_sendData.message.header.type = MessageType::CommunicationSuccess;
					SendMessageData(m_sendData);
					break;
				}
				//----------//
				// 通信成功 //
				case MessageType::CommunicationSuccess:
					if (!m_isCommunicationData)
					{
						// 通信の開始を設定
						m_isCommunicationData = true;
						m_isCommunicationDuring = false;
						// 自身の番号を代入
						m_myServerNo = m_receiveData.message.header.userNo;
						// システム通知を表示
						MessageBoxW(NULL, L"サーバーにログインしました", L"システム通知", MB_OK);
						break;
					}
				//----------//
				// 通信終了 //
				case MessageType::CommunicationEnd:
					// オーナーの場合
					if (m_myServerRank == ServerRank::Owner)
					{
						// 削除するユーザーイテレーター
						std::list<CommunicationUserData>::iterator eraseUser;

						// 通信中のユーザー数だけループ
						for (auto it = m_comUserList.begin(); it != m_comUserList.end(); it++)
						{
							CommunicationUserData comUser = *it;
							// IPアドレスとポート番号が送信元と同じ？
							if (comUser.address.sin_addr.S_un.S_addr == m_sendAddress.sin_addr.S_un.S_addr &&
								comUser.address.sin_port == m_sendAddress.sin_port)
							{
								// ===== ロック状態の解除 ===== //
								std::list<std::list<RockObjectData>::iterator> eraseIteratorList;	// 削除する要素を格納しておくリスト

								// ロックされているオブジェクト分ループ
								for (auto it = m_rockObjectList.begin(); it != m_rockObjectList.end(); it++)
								{
									RockObjectData rockObject = *it;
									// ロックしているユーザーと送信元ユーザーが一致？
									if (rockObject.rockUserNo == m_receiveData.message.header.userNo)
									{
										eraseIteratorList.push_back(it);	// 削除する要素として格納
									}
								}
								// 削除する要素分ループ
								for (auto it : eraseIteratorList)
								{
									m_rockObjectList.erase(it);	// 要素を削除

									// 他ユーザーのロック状態を解除
									m_receiveData.message.header.type = MessageType::ClickObject;
									m_receiveData.message.body.object.CopyName(nullptr);
									SendMessageOtherUser(m_receiveData);
								}

								// 削除するユーザーのイテレーターを代入
								eraseUser = it;
							}
						}
						// ユーザーリストから除外
						m_comUserList.erase(eraseUser);
						// システム通知
						MessageBoxW(NULL, L"ユーザーがログアウトしました", L"システム通知", MB_OK);
					}
					// ユーザーの場合
					else if (m_myServerRank == ServerRank::User)
					{
						// シャットダウンされたことを記録
						m_isServerShutdown = true;
						// システム通知
						MessageBoxW(NULL, L"サーバーが閉じました", L"システム通知", MB_OK);
					}
					break;
				//--------------------//
				// コンポーネント更新 //
				case MessageType::UpdateComponent:
					// ===== コンポーネントの種類によって処理を分岐 ===== //
					// Transformコンポーネント
					if (strcmp(m_receiveData.message.body.componentType, "Transform") == 0)
					{
						// コンポーネント取得
						Transform* transform =
							Ctlan::PublicSystem::SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->transform;
						// 各値を代入
						*transform = Transform(m_receiveData.message.body.transform);
					}
					// Textコンポーネント
					else if (strcmp(m_receiveData.message.body.componentType, "Text") == 0)
					{
						// コンポーネント取得
						Text* text =
							SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->GetComponent<Text>();
						// 各値を代入
						*text = Text(m_receiveData.message.body.text);
					}
					SendMessageOtherUser(m_receiveData);
					break;
				//------------------//
				// オブジェクト選択 //
				case MessageType::ClickObject:
				{
					bool isRocked = false;	// 既にロックされているかどうか

					// ロックされているオブジェクト分ループ
					for (RockObjectData& rockObject : m_rockObjectList)
					{
						// 送信元ユーザーは既にオブジェクトをロックしている？
						if (rockObject.rockUserNo == m_receiveData.message.header.userNo)
						{
							// クリックされたオブジェクト名を代入
							strcpy_s(rockObject.rockObjectName, m_receiveData.message.body.object.GetName());
							isRocked = true;	// 既にロックしていることを覚えておく
							break;
						}
					}
					// まだロックされていないオブジェクト？
					if (!isRocked)
					{
						// 登録処理
						RockObjectData rockObjectData;
						// クリックされたオブジェクト名を代入
						strcpy_s(rockObjectData.rockObjectName, m_receiveData.message.body.object.GetName());
						rockObjectData.rockUserNo = m_receiveData.message.header.userNo;
						m_rockObjectList.push_back(rockObjectData);
					}

					SendMessageOtherUser(m_receiveData);	// 他ユーザーにメッセージ送信
					break;
				}
				//------------------//
				// オブジェクト削除 //
				case MessageType::ObjectDelete:
					// 受信データ内からオブジェクト名を取得し、そのオブジェクトを削除
					Ctlan::PublicSystem::SceneManager::GetNowScene()->DeleteSceneObject(m_receiveData.message.body.object.GetName());
					SendMessageOtherUser(m_receiveData);
					break;
				//--------------//
				// キューブ作成 //
				case MessageType::CreateCube:
				{
					// キューブを作成し、作成したキューブを取得しておく
					GameObject* cubeObject = Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateCube>(1, "Cube");
					// メッセージからTransform情報を取得し、代入
					// ※作成した際、座標以外は一定の値なので、代入しない
					cubeObject->transform->position = m_receiveData.message.body.transform.position;
					SendMessageOtherUser(m_receiveData);
					break;
				}
				//--------------//
				// テキスト作成 //
				case MessageType::CreateText:
				{
					// テキストを作成
					Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateText>(3, "Text");
					SendMessageOtherUser(m_receiveData);
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

void Server::CommunicationStartThread()
{
	double timer = 0;			// メッセージを送るまでの時間
	int sendMessageCount = 0;	// メッセージを送った回数
	// 通信成功or規定回数メッセージを送るまでループ
	while (!m_isCommunicationData && sendMessageCount <= 10)
	{
		// 既定秒数が経過した？
		if (timer >= 1000000)
		{
			// 相手に通信開始通知を送る
			m_sendData.message.header.type = MessageType::CommunicationStart;
			SendMessageData(m_sendData);
			sendMessageCount++;
			timer = 0;
		}
		else
		{
			// タイマーの秒数を増やす
			timer += Ctlan::PublicSystem::Time::DeltaTime * 0.00006f;
		}
	}

	// メッセージを送ったが、返答がなかった？
	if (!m_isCommunicationData)
		m_isCommunicationDuring = false;
		// メッセージ通知
		MessageBoxW(NULL, L"ログインに失敗しました", L"システム通知", MB_OK);
	return;
}

void Server::SendMessageOtherUser(MessageData& sendMessage)
{
	// 自身がサーバーを開いた？
	if (m_myServerRank == Owner)
	{
		// ユーザーが複数人いる？
		if (m_comUserList.size() > 1)
		{
			// ユーザー数だけループ
			for (const CommunicationUserData& data : m_comUserList)
			{
				// 送信元ユーザーではないユーザー？
				if (data.userNo != sendMessage.message.header.userNo)
				{
					m_sendAddress = data.address;	// アドレス設定
					SendMessageData(sendMessage);	// メッセージ送信
				}
			}
		}
	}
}

Server::~Server()
{
	// 通信を行っている？
	if (m_isCommunicationData)
	{
		// 自身の地位によって処理を分ける
		switch (m_myServerRank)
		{
			//----------//
			// ユーザー //
			case User:
				LogoutServer();
				break;
			//----------//
			// オーナー //
			case Owner:
				CloseServer();
				break;
		}
	}

	if(m_receiveThread.joinable())
		// 受信スレッド終了
		m_receiveThread.join();
	if (m_comStartThread.joinable())
		m_comStartThread.join();
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

		// 受信スレッドが生成されていない？
		if (!m_receiveThread.joinable())
			// 受信スレッド生成
			m_receiveThread = std::thread(&Server::ReceiveThread, this);

		MessageBoxW(NULL, L"サーバーを開きました", L"システム通知", MB_OK);
	}
}
 
void Server::CloseServer()
{
	// オーナーとして、データの通信を行っている？
	if (m_isCommunicationData && m_myServerRank == Owner)
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
		m_isCommunicationDuring = false;
		// ロック状態の解除
		m_rockObjectList.clear();

		// スレッドの終了を待つ
		m_receiveThread.join();

		// WINSOCKの終了処理
		WSACleanup();

		MessageBoxW(NULL, L"サーバーを閉じました", L"システム通知", MB_OK);
	}
	else
	{
		// メッセージ表示
		MessageBoxW(NULL, L"あなたはサーバーを開いていません", L"システム通知", MB_OK);
	}
}

void Server::LoginServer()
{
	// 通信を行っていない？
	if (!m_isCommunicationData && !m_isCommunicationDuring)
	{
		WSADATA wsaData;	// WinSockの初期化データを格納
		WORD	verNo;		// バージョン指定

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

		char str[256]{};
		rewind(stdin);
		int r = scanf_s("%s", str, 256);

		// 宛先のアドレスを設定
		m_sendAddress.sin_port = htons(PORTNO);	// ポート番号（16ビット）をネットワークバイトオーダーに変更
		m_sendAddress.sin_family = AF_INET;
		// 10進表記のIPアドレスを32ビットに変換（ネットワークバイトオーダー）
		m_sendAddress.sin_addr.S_un.S_addr = inet_addr(str);

		// 地位を設定
		m_myServerRank = User;
		// 通信開始中の状態に変更
		m_isCommunicationDuring = true;

		// 受信スレッドが生成されていない？
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
	// ユーザーとして、通信を行っている？
	if (m_isCommunicationData && m_myServerRank == User)
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
		// 通信状態を初期化
		m_isCommunicationData = false;
		m_isCommunicationDuring = false;
		// シャットダウン状態を初期化
		m_isServerShutdown = false;
		// ロック状態の解除
		m_rockObjectList.clear();

		// スレッドの終了を待つ
		if(m_receiveThread.joinable())
			m_receiveThread.join();

		// WINSOCKの終了処理
		WSACleanup();

		// メッセージ表示
		MessageBoxW(NULL, L"サーバーからログアウトしました", L"システム通知", MB_OK);
	}
	else
	{
		// メッセージ表示
		MessageBoxW(NULL, L"あなたはサーバーにログインしていません", L"システム通知", MB_OK);
	}
}

void Server::SendMessageData(MessageData& messageData)
{
	if (m_isCommunicationData || messageData.message.header.type == MessageType::CommunicationStart)
	{
		// ===== その他に送る情報を代入 ===== //
		// サーバーが送信元以外のユーザーにメッセージを送る？
		if (m_myServerRank == Owner && messageData.message.header.userRank == User)
		{
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
			return;	// 処理を終了
		}
		// 通常処理
		else
		{
			// 各値を代入
			// ユーザーランク
			messageData.message.header.userRank = m_myServerRank;
			// ユーザー番号
			messageData.message.header.userNo = m_myServerNo;
		}

		// ===== 送信処理 ===== //
		// 複数人のユーザーと通信している？
		if (m_comUserList.size() > 1)
		{
			// ユーザー数だけループ
			for (const CommunicationUserData& data : m_comUserList)
			{
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
		else
		{
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
}

const int Server::GetRockUserNo(const char* objectName)
{
	// ロックしていない？
	if (m_rockObjectList.empty())
		return m_myServerNo;

	// ロックしているオブジェクト分ループ
	for (const RockObjectData& rockObject : m_rockObjectList)
	{
		// オブジェクト名がロックしているオブジェクト名と一致した？
		if (rockObject.rockObjectName != nullptr && strcmp(rockObject.rockObjectName, objectName) == 0)
			return rockObject.rockUserNo;
	}
	return m_myServerNo;
}

bool Server::IsRockObject(const char* objectName)
{
	// ロックしていない？
	if (m_rockObjectList.empty())
		return false;

	// ロックしているオブジェクト分ループ
	for (const RockObjectData& rockObject : m_rockObjectList)
	{
		// オブジェクト名がロックしているオブジェクト名と一致した？
		if (rockObject.rockObjectName != nullptr && strcmp(rockObject.rockObjectName, objectName) == 0)
			return true;
	}
	return false;
}
