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
		// ----- structs / 構造体 ----- //
		/// <summary>
		///	送受信用のメッセージ	</summary>
		struct MessageData
		{
			int randNum = 0;
			char receiveMessage[65535];
			char sendMessage[256];
		};

		// ---- enums / 列挙型 ----- //
		/// <summasy>
		/// サーバーでの地位 </summary>
		enum ServerRank
		{
			/// <summary>
			///	サーバーを立てた人物	</summary>
			Owner,
			/// <summary>
			///	サーバーに来た人物	</summary>
			User
		};
		
		// ----- variables / 変数 ----- //
		/// <summary>
		///	自身のソケット情報	</summary>
		SOCKET m_mySocket;
		/// <summary>
		///	自身のアドレス	</summary>
		sockaddr_in m_myAddress{};
		/// <summary>
		///	送信先アドレス	</summary>
		sockaddr_in m_sendAddress{};

		/// <summary>
		///	受信スレッド	</summary>
		std::thread m_receiveThread;
		/// <summary>
		///	送受信メッセージ	</summary>
		MessageData m_messageData;

		/// <summary>
		/// データの通信状態 </summary>
		bool m_isCommunicationData;
		/// <summary>
		///	自身のサーバーでの地位	</summary>
		ServerRank m_myServerRank;

		// ロックしているオブジェクト名
		char rockObjectName[30];

		// ----- functions / 関数 ----- //
		/// <summary>
		/// 受信スレッド	</summary>
		void ReceiveThread();
		
		void TestThread();
		std::thread testThread;


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
		/// <summary>
		///	サーバーにログインする	</summary>
		void LoginServer();
		/// <summary>
		///	サーバーからログアウトする	</summary>
		void LogoutServer();
		/// <summary>
		/// データを送信する	</summary>
		void SendData();
		/// <summary>
		///	メッセージデータを送信する	</summary>
		/// <param name="message">
		/// 送信するメッセージ	</param>
		void SendData(const char* message);
		
		/// <summary>
		///	オブジェクトがロックされているか判定	</summary>
		/// <param name="objectName">
		///	判定するオブジェクト名	</param>
		/// <returns>
		///	ロックされていたらtrue、されていなければfalseを返す	</returns>
		bool IsRockObject(const char* objectName);
};

