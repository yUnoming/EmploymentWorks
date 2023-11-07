#pragma once
/**
* @file		yUno_MainManager.h
* @brief	yUno_MainManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"

/// <summary>
/// メインでシステムを回すためのクラス	</summary>
class yUno_MainManager
{
	private:
		// ----- variables / 変数 ----- //
		/// <summary>
		/// 現在のシーン	</summary>
		static yUno_SceneManager* m_NowScene;
		/// <summary>
		/// 現在のプレイ状態	</summary>
		static bool m_DemoPlay;

	public:
		// ----- methods / 関数 ----- //
		/// <summary>
		/// 初期化	</summary>
		/// <param name="app">
		/// アプリケーション情報	</param>
		static void Init(Application* app);
		/// <summary>
		/// 終了	</summary>
		static void UnInit();
		/// <summary>
		///	更新	</summary>
		static void Update();
		/// <summary>
		/// 描画	</summary>
		static void Draw();
};
