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

namespace Ctlan
{
	namespace PrivateSystem
	{
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
					/// ユーザー番号 </summary>
					int userNo;
					/// <summary>
					///	ユーザーアドレス	</summary>
					sockaddr_in address;
				};

				/// <summary>
				///	ロックオブジェクト情報	</summary>
				struct RockObjectData
				{
					/// <summary>
					/// ロックしているオブジェクト名	<summary>
					char rockObjectName[30];
					/// <summary>
					///	ロックしているユーザー番号	</summary>
					int rockUserNo;
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
				/// <summary>
				///	自身のサーバーで付与された番号	</summary>
				int m_myServerNo;

				/// <summary>
				///	通信ユーザーリスト	</summary>
				std::list<CommunicationUserData> m_comUserList;

				/// <summary>
				///	ロックオブジェクトリスト	</summary>
				std::list<RockObjectData> m_rockObjectList;

				// ----- functions / 関数 ----- //
				/// <summary>
				/// 受信スレッド	</summary>
				void ReceiveThread();
				/// <summary>
				///	受信開始スレッド	</summary>
				void CommunicationStartThread();

				/// <summary>
				///	他ユーザーにメッセージを送る	</summary>
				void SendMessageOtherUser(MessageData& sendMessage);

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
				///	ロックされたオブジェクトを操作しているユーザーの番号を取得	</summary>
				/// <param name="objectName">
				///	ロックされたオブジェクト名	</param>
				/// <returns>
				///	ユーザー番号	</returns>
				const int GetRockUserNo(const char* objectName);
				/// <summary>
				///	オブジェクトがロックされているか判定	</summary>
				/// <param name="objectName">
				///	判定するオブジェクト名	</param>
				/// <returns>
				///	ロックされていたらtrue、されていなければfalseを返す	</returns>
				bool IsRockObject(const char* objectName);
		};
	}
}