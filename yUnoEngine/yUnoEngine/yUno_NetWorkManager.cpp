#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

constexpr unsigned short PORTNO = 49152;

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#pragma comment(lib, "ws2_32.lib")

#include "yUno_NetWorkManager.h"

#include <winsock2.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <iostream>

int yUno_SystemManager::yUno_NetWorkManager::Start()
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
		return 0;
	}

	// 要求したバージョンを利用できるか確認する
	if (verNo != wsa.wVersion)
	{
		std::cout << "要求したバージョンは利用できません" << std::endl;
		return 0;
	}

	// ソケット生成
	SOCKET mySocket;		// ソケット
	mySocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mySocket == INVALID_SOCKET)
	{
		std::cout << "ソケットの生成に失敗しました" << std::endl;
		return 0;
	}

	// 自身のアドレスを設定
	sockaddr_in myAddress{};	// 自身のアドレス
	myAddress.sin_port = htons(PORTNO);
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// 自分のソケットにIPアドレス、ポート番号を割り当てる
	sts = bind(mySocket, (sockaddr*)&myAddress, sizeof(sockaddr));
	if (sts == SOCKET_ERROR)
	{
		std::cout << "ソケットへの割り当てに失敗しました" << std::endl;
		return 0;
	}

}

int yUno_SystemManager::yUno_NetWorkManager::End()
{
	//　ソケットをクローズ時、エラーが発生した？
	//if (closesocket(mysocket) != 0)
	//{
	//	int errorCode = WSAGetLastError();
	//	std::cout << "closesocket() Failed ErrorCode：" << errorCode << std::endl;
	//	return 0;
	//}

	// WINSOCKの終了処理
	WSACleanup();
	return 0;
}
