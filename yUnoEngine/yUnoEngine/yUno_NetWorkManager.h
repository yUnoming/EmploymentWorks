#pragma once
/**
* @file		Component.h
* @brief	Componentクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <WinSock2.h>
#include <thread>

namespace yUno_SystemManager
{
	/// <summary>
	///	ネットワークの処理を管理するクラス	</summary>
	class yUno_NetWorkManager
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
			/// 通信開始しているかどうか	</summary>
			bool isCommunication;
			/// <summary>
			/// 受信待ち状態かどうか </summary>
			bool isReceiveWaiting;


			// ----- functions / 関数 ----- //
			/// <summary>
			/// 受信スレッド	</summary>
			void ReceiveThread();

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			///	ネットワーク通信を開始	</summary>
			int Start();
			/// <summary>
			///	ネットワーク通信を終了	</summary>
			int End();
	};
}

