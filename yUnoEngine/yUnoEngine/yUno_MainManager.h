#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"


class yUno_MainManager
{
	private:
		// ----- variables ----- //
		// 現在の開いているシーン
		yUno_SceneManager* m_NowScene;

		// デモプレイ中かどうか
		static bool m_DemoPlay;

	public:
		// ----- methods ----- //
		static void Init();
		static void UnInit();
		static void Update();
		static void Draw();
};
