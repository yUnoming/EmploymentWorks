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

		memset(m_messageData.receiveMessage, 0, sizeof(m_messageData.receiveMessage));

		int sts = recvfrom(
			m_mySocket,
			(char*)m_messageData.receiveMessage,
			sizeof(m_messageData.receiveMessage),
			0,
			(sockaddr*)&m_sendAddress,
			&myAddressLength);

		if (sts != SOCKET_ERROR)
		{
			if (strcmp(m_messageData.receiveMessage, "LoginSuccess") == 0)
			{
				std::cout << "Login Server" << std::endl;
			}
			else if (strcmp(m_messageData.receiveMessage, "ServerLogin") == 0)
			{
				printf("受信データ : %s \n", m_messageData.receiveMessage);
				printf("送信元ＩＰアドレス/ポート番号 %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));

				strcpy_s(m_messageData.sendMessage, sizeof(m_messageData.sendMessage), "LoginSuccess");
				int len = static_cast<int>(strlen(m_messageData.sendMessage));	// 送信文字列長を取得
				sts = sendto(
					m_mySocket,					// ソケット番号
					m_messageData.sendMessage,	// 送信データ
					len,						// 送信データ長
					0,							// フラグ
					(sockaddr*)&m_sendAddress,	// 送信先アドレス
					sizeof(sockaddr));			// アドレス構造体のバイトサイズ
			}
			else
			{
				printf("受信データ : %s %d \n", m_messageData.receiveMessage, m_messageData.randNum);
				printf("送信元ＩＰアドレス/ポート番号 %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));
				
				
				char* context;
				char* msgType = strtok_s(m_messageData.receiveMessage, " ", &context);
				int msgTypeNo = strtof(msgType, NULL);

				// メッセージのタイプにより、処理を分岐
				switch (msgTypeNo)
				{
					// コンポーネントの値更新
					case yUno_SystemManager::yUno_NetWorkManager::MessageType::UpdateComponentValue:
					{
						// 残りの情報を読み取る
						char* objName = strtok_s(NULL, " ", &context);
						char* comType = strtok_s(NULL, " ", &context);
						char* varName = strtok_s(NULL, " ", &context);
						char* xParam = strtok_s(NULL, " ", &context);
						char* yParam = strtok_s(NULL, " ", &context);
						char* zParam = strtok_s(NULL, " ", &context);
						if (objName != nullptr && xParam != nullptr && yParam != nullptr && zParam != nullptr)
						{
							float newX = strtof(xParam, NULL);
							float newY = strtof(yParam, NULL);
							float newZ = strtof(zParam, NULL);
							SceneManager::GetNowScene()->GetSceneObject(objName)->transform->Position = Vector3(newX, newY, newZ);
							memcpy(g_rockObject, objName, strlen(objName));
						}
						break;
					}
					case yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject:
					{
						// 残りの情報を読み取る
						char* objName = strtok_s(NULL, " ", &context);
						strcpy_s(rockObjectName, objName);
						break;
					}
				}
			}
		}
		// 通信を終了した？
		else if (!m_isCommunicationData)
		{
			// ループを抜ける
			break;
		}
		else
		{
			std::cout << "エラーが発生した" << std::endl;
		}
	}
	return;
}

void Server::TestThread()
{
	//std::array<std::list<GameObject*>, 4> lateSceneObject = SceneManager::GetSceneObjectAll();
	//std::list<GameObject> lateObjects;
	//Transform moveObject;

	//for (auto& lateObjectList : lateSceneObject)
	//{
	//	for (auto& lateObject : lateObjectList)
	//	{
	//		lateObjects.push_back(*lateObject);
	//	}
	//}

	//while (true)
	//{
	//	if (!m_isCommunicationData)
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		for (auto& lateObject : lateObjects)
	//		{
	//			auto object = SceneManager::GetNowScene()->GetSceneObject(lateObject.GetName());

	//			if (lateObject.transform->Position != object->transform->Position &&
	//				strcmp(lateObject.GetName(), "SpectatorCamera") != 0 && (g_rockObject == NULL || strcmp(lateObject.GetName(), g_rockObject) != 0))
	//			{
	//				char sendData[100];
	//				sprintf_s(sendData, "%s %f %f %f", lateObject.GetName(), object->transform->Position.x, object->transform->Position.y, object->transform->Position.z);
	//				SendData(sendData);
	//				lateObject = *object;
	//			}
	//		}
	//	}
	//}
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
		testThread = std::thread(&Server::TestThread, this);

		std::cout << "NetWork Communication Start" << std::endl;
	}
}

void Server::CloseServer()
{
	// データの通信を行っている？
	if (m_isCommunicationData)
	{
		//　ソケットをクローズ時、エラーが発生した？
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode：" << errorCode << std::endl;
		}
		// 通信の終了を設定
		m_isCommunicationData = false;

		// スレッドの終了を待つ
		m_receiveThread.join();
		testThread.join();

		// WINSOCKの終了処理
		WSACleanup();

		std::cout << "NetWork Communication End" << std::endl;
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

		// 通信の開始を設定
		m_isCommunicationData = true;
		// 地位を設定
		m_myServerRank = User;

		// 受信スレッド生成
		m_receiveThread = std::thread(&Server::ReceiveThread, this);
		testThread = std::thread(&Server::TestThread, this);
	}
}

void Server::LogoutServer()
{
	// 通信を行っている？
	if (m_isCommunicationData)
	{
		//　ソケットをクローズ時、エラーが発生した？
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode：" << errorCode << std::endl;
		}
		// 通信の終了を設定
		m_isCommunicationData = false;

		// スレッドの終了を待つ
		m_receiveThread.join();

		// WINSOCKの終了処理
		WSACleanup();
	}
	std::cout << "Logout Server" << std::endl;
}

void Server::SendData()
{
	if (m_isCommunicationData)
	{
		// 送信データ作成
		printf("\n送信データを入力してください（アルファベットのみ）\n");
		rewind(stdin);
		int r = scanf_s("%[^\n]", m_messageData.sendMessage, 255);	// 改行以外を読み込む

		size_t len = strlen(m_messageData.sendMessage);		// 送信文字列長を取得

		// データの送信時、エラーが発生した？
		if (sendto(
			m_mySocket,							// ソケット番号
			m_messageData.sendMessage,			// 送信データ
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

void Server::SendData(const char* message)
{
	if (m_isCommunicationData)
	{
		strcpy_s(m_messageData.sendMessage, sizeof(m_messageData.sendMessage), message);
		size_t len = strlen(m_messageData.sendMessage);		// 送信文字列長を取得


		// データの送信時、エラーが発生した？
		if (sendto(
			m_mySocket,							// ソケット番号
			m_messageData.sendMessage,			// 送信データ
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

bool Server::IsRockObject(const char* objectName)
{
	// ロックされていない？別のオブジェクトをロックしている？
	if (rockObjectName == nullptr || strcmp(rockObjectName, objectName) != 0)
		return false;
	return true;
}
