#pragma once
/**
* @file		SystemMainManager.h
* @brief	SystemMainManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemSceneManager.h"

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			/// メインでシステムを回すためのクラス	</summary>
			class SystemMainManager
			{
				private:
					// ----- variables / 変数 ----- //
					/// <summary>
					/// 現在のプレイ状態	</summary>
					static bool m_demoPlay;

				public:
					// ----- functions / 関数 ----- //
					/// <summary>
					/// 初期化	</summary>
					/// <param name="app">
					/// アプリケーション情報	</param>
					static void Init(Application* app);
					/// <summary>
					/// 終了	</summary>
					static void Uninit();
					/// <summary>
					///	更新	</summary>
					static void Update();
					/// <summary>
					/// 描画	</summary>
					static void Draw();
			};
		}
	}
}
