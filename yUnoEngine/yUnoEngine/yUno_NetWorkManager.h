#pragma once
/**
* @file		yUno_NetWorkManager.h
* @brief	yUno_NetWorkManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.16
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Server.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 マクロ定義		　　  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //

namespace yUno_SystemManager
{
	/// <summary>
	///	ネットワークの処理を管理するクラス	</summary>
	class yUno_NetWorkManager
	{
		private:
			// ----- variables / 変数 ----- //
			/// <summary>
			/// サーバー	</summary>
			static Server* m_Server;

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			///	初期化	</summary>
			static void Init();
			/// <summary>
			/// 終了	</summary>
			static void UnInit();
			
			/// <summary>
			///	サーバー情報を取得	</summary>
			/// <returns>
			/// サーバー情報を返す	</returns>
			static Server* GetServer() { return m_Server; };
	};
}

