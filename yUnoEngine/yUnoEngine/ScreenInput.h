#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"


namespace PublicSystem
{
	// 画面入力に関する処理をまとめたクラス
	class ScreenInput
	{
		public:
			// ----- functions / 関数 ----- //

			// 指定した座標をスクリーン座標に変換して返す関数
			static Vector2 GetScreenPosition(Vector2 _paramPosition);
	};
}

