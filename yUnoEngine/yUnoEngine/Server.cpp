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

#include <stdio.h>
#include <time.h>
#include <iostream>


void Server::ReceiveThread()
{
	int			errcode;	// ＷＩＮＳＯＣＫのエラーコード
	sockaddr_in fromaddr{};	// 送信元アドレス
	int fromAddrLength = 0;	// 送信元アドレスがセットされる変数の長さ
	// サーバーを開いた状態にする
	isOpenServer = true;

	while (true)
	{
		fromAddrLength = sizeof(sockaddr);

		memset(m_receiveBuffer, 0, sizeof(m_receiveBuffer));

		int sts = recvfrom(
			m_mySocket,
			(char*)m_receiveBuffer,
			sizeof(m_receiveBuffer),
			0,
			(sockaddr*)&fromaddr,
			&fromAddrLength);

		if (sts != SOCKET_ERROR)
		{
			printf("受信データ : %s \n", m_receiveBuffer);
			printf("送信元ＩＰアドレス/ポート番号 %s/%d \n",
				inet_ntoa(fromaddr.sin_addr),
				ntohs(fromaddr.sin_port));

			// 受信データロギング
			//loggingdata(m_receiveBuffer, fromaddr);

			int len = static_cast<int>(strlen(m_sendBuffer));	// 送信文字列長を取得
			sts = sendto(
				m_mySocket,				// ソケット番号
				m_sendBuffer,			// 送信データ
				len,					// 送信データ長
				0,						// フラグ
				(sockaddr*)&fromaddr,	// 送信先アドレス
				sizeof(sockaddr));		// アドレス構造体のバイトサイズ
		}
		// サーバーが閉じた状態になった？
		else if (!isOpenServer)
		{
			// ループを抜ける
			break;
		}
	}
	return;
}

Server::~Server()
{
	// サーバーが開いている？
	if (isOpenServer)
		// サーバーを閉じる
		CloseServer();
}

void Server::OpenServer()
{
	WSADATA wsa;	// WinSockの初期化データを格納
	WORD	verNo;	// バージョン指定
	int sts;		// WinSockが正しく初期化されたか代入

	// バージョン2.2を要求
	verNo = MAKEWORD(2, 2);

	// WinSock初期化時、エラーが発生した？
	if (WSAStartup(
		verNo,	// 要求バージョン
		&wsa)	// WinSockデータを格納するための変数
		== SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		std::cout << "WSAStartup() Failed!!! ErrorCode：" << errorCode << std::endl;
		return;
	}

	// 要求したバージョンを利用できるか確認する
	if (verNo != wsa.wVersion)
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

	// 自分のソケットにIPアドレス、ポート番号を割り当てる
	sts = bind(m_mySocket, (sockaddr*)&myAddress, sizeof(sockaddr));
	if (sts == SOCKET_ERROR)
	{
		std::cout << "ソケットへの割り当てに失敗しました" << std::endl;
		return;
	}

	// 受信スレッド生成
	m_receiveThread = std::thread(&Server::ReceiveThread, this);

	std::cout << "NetWork Communication Start" << std::endl;
}

void Server::CloseServer()
{
	// サーバーが開いている？
	if (isOpenServer)
	{
		//　ソケットをクローズ時、エラーが発生した？
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode：" << errorCode << std::endl;
		}
		// サーバーを閉じた状態にする
		isOpenServer = false;

		// スレッドの終了を待つ
		m_receiveThread.join();

		// WINSOCKの終了処理
		WSACleanup();

		std::cout << "NetWork Communication End" << std::endl;
	}
}
