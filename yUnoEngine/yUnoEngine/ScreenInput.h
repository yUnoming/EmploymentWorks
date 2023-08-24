#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"


namespace PublicSystem
{
	class ScreenInput
	{
		public:
			// ----- functions / 関数 ----- //

			// 指定した座標をスクリーン座標に変換して返す関数
			static Vector2 GetScreenPosition(Vector2 _paramPosition);
	};
}

