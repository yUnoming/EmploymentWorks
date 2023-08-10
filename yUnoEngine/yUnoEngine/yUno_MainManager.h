#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"

class yUno_MainManager
{
	private:
		// ----- variables / 変数 ----- //
		// 現在のシーン
		static yUno_SceneManager* m_NowScene;

		// デモプレイ中かどうか
		static bool m_DemoPlay;

	public:
		// ----- methods / 関数 ----- //
		static void Init(Application* app);
		static void UnInit();
		static void Update();
		static void Draw();
};
