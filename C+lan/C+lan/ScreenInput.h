#pragma once
/**
* @file		ScreenInput.h
* @brief	ScreenInputクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// // 画面入力に関する機能をまとめたクラス	</summary>
		class ScreenInput
		{
		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			///	指定した座標をスクリーン座標に変換して返す関数	</summary>
			/// <param name="paramPosition">
			///	変換したい座標	</param>
			/// <returns>
			/// 変換したスクリーン座標 </returns>
			static Vector2 GetScreenPosition(Vector2 paramPosition);
		};
	}
}