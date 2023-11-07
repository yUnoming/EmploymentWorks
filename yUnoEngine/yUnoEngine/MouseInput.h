#pragma once
/**
* @file		MouseInput.h
* @brief	MouseInputクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.05
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector2.h"


namespace PublicSystem
{
	/// <summary>
	///	マウス入力を判定するための機能をまとめたクラス	</summary>
	class MouseInput
	{
		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			/// 現在のカーソル座標を取得	</summary>
			/// <returns>
			/// 現在のカーソル座標	</returns>
			static Vector2 GetCursorPosition();

			/// <summary>
			/// マウスが押された瞬間かどうかを判定	</summary>
			/// <param name = "button">
			/// 判定するマウスのボタン名	</param>
			/// <returns>
			/// 押された瞬間ならtrue、それ以外ならfalse	</returns>
			static bool GetMouseDownTrigger(PublicSystem::MouseButtonName button);
			/// <summary>
			/// マウスが押されているかどうかを判定	</summary>
			/// <param name = "button">
			/// 判定するマウスのボタン名	</param>
			/// <returns>
			/// 押されているならtrue、それ以外ならfalse	</returns>
			static bool GetMouseDown(PublicSystem::MouseButtonName button);
			
			/// <summary>
			///	マウスが離された瞬間かどうかを判定	</summary>
			/// <param name="button">
			///	判定するマウスのボタン名	</param>
			/// <returns>
			///	離された瞬間ならtrue、それ以外ならfalse	</returns>
			static bool GetMouseUpTrigger(PublicSystem::MouseButtonName button);
			/// <summary>
			///	マウスが離されているかどうかを判定	</summary>
			/// <param name="button">
			///	判定するマウスのボタン名	</param>
			/// <returns>
			///	離されているならtrue、それ以外ならfalse	</returns>
			static bool GetMouseUp(PublicSystem::MouseButtonName button);

			/// <summary>
			/// マウスホイールが回転されているかどうかを判定	</summary>
			/// <returns>
			/// 回転されているならtrue、それ以外ならfalse	</returns>
			static bool GetWheelRotation();
			/// <summary>
			/// マウスホイールが前方回転されているかどうかを判定	</summary>
			/// <returns>
			/// 前方回転されているならtrue、それ以外ならfalse	</returns>
			static bool GetWheelRotationForward();
			/// <summary>
			/// マウスホイールが後方回転されているかどうかを判定	</summary>
			/// <returns>
			/// 後方回転されているならtrue、それ以外ならfalse	</returns>
			static bool GetWheelRotationBackward();
	};
}

