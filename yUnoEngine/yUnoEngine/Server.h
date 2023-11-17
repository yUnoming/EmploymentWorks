#pragma once
/**
* @file		Server.h
* @brief	Serverクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.16
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <WinSock2.h>
#include <thread>


/// <summary>
///	サーバーを扱うためのクラス	</summary>
class Server
{
	private:
		// ----- variables / 変数 ----- //
		/// <summary>
		///	自身のソケット情報	</summary>
		SOCKET m_mySocket;
		/// <summary>
		///	受信スレッド	</summary>
		std::thread m_receiveThread;
		/// <summary>
		///	受信バッファ	</summary>
		char m_receiveBuffer[65535]{};
		/// <summary>
		/// 送信バッファ	</summary>
		char m_sendBuffer[256] = { "データ受信しました" };

		/// <summary>
		/// サーバーが開いているかどうか </summary>
		bool isOpenServer;


		// ----- functions / 関数 ----- //
		/// <summary>
		/// 受信スレッド	</summary>
		void ReceiveThread();


	public:
		// ----- functions / 関数 ----- //
		// デストラクタ
		~Server();

		/// <summary>
		///	サーバーを開く	</summary>
		void OpenServer();
		/// <summary>
		///	サーバーを閉じる	</summary>
		void CloseServer();
};

