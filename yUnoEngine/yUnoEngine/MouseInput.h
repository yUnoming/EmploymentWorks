#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"
#include "InputPartsName.h"


namespace PublicSystem
{
	class MouseInput
	{
		public:
			// ----- functions / 関数 ----- //

			// 現在のカーソル座標を返す関数
			static Vector2 GetCursorPosition();

			// マウスが押された瞬間をかどうかを返す関数
			static bool GetMouseDown_Trigger(MouseButtonName _mb);
			// マウスが押されているかどうかを返す関数
			static bool GetMouseDown(MouseButtonName _mb);
	};
}

