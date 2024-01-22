#pragma once
/**
* @file		SystemNetWorkManager.h
* @brief	SystemNetWorkManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.16
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Server.h"


namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	ネットワークの処理を管理するクラス	</summary>
			class SystemNetWorkManager
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
					static void Uninit();

					/// <summary>
					///	サーバー情報を取得	</summary>
					/// <returns>
					/// サーバー情報を返す	</returns>
					static Server* GetServer() { return m_Server; };
			};
		}
	}
}

