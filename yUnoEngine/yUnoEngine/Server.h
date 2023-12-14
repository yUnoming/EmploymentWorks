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
#include "Message.h"


/// <summary>
///	サーバーを扱うためのクラス	</summary>
class Server
{
	private:
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
		// ----- structs / 構造体 ----- //
		/// <summary>
		///	通信ユーザー情報	</summary>
		struct CommunicationUserData
		{
			/// <summary>
			///	ユーザーランク	</summary>
			ServerRank userRank;
			/// <summary>
			///	ユーザーアドレス	</summary>
			sockaddr_in address;
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
		sockaddr_in m_receiveAddress{};
		/// <summary>
		///	送信データ	</summary>
		MessageData m_sendData;
		/// <summary>
		///	受信データ	</summary>
		MessageData m_receiveData;
		
		/// <summary>
		///	受信スレッド	</summary>
		std::thread m_receiveThread;
		/// <summary>
		///	受信開始用スレッド	</summary>
		std::thread m_comStartThread;

		/// <summary>
		/// データの通信状態 </summary>
		bool m_isCommunicationData;
		/// <summary>
		///	通信開始の最中かどうか	</summary>
		bool m_isCommunicationDuring;

		/// <summary>
		///	自身のサーバーでの地位	</summary>
		ServerRank m_myServerRank;

		// ロックしているオブジェクト名
		char rockObjectName[30];

		/// <summary>
		///	通信ユーザーリスト	</summary>
		std::list<CommunicationUserData> m_comUserList;

		// ----- functions / 関数 ----- //
		/// <summary>
		/// 受信スレッド	</summary>
		void ReceiveThread();
		/// <summary>
		///	受信開始スレッド	</summary>
		void CommunicationStartThread();

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
		void SendMessageData(MessageData& messageData);
		


		/// <summary>
		///	オブジェクトがロックされているか判定	</summary>
		/// <param name="objectName">
		///	判定するオブジェクト名	</param>
		/// <returns>
		///	ロックされていたらtrue、されていなければfalseを返す	</returns>
		bool IsRockObject(const char* objectName);
};

