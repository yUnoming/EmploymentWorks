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

			/// <summary>
			/// 現在のカーソル座標を取得する	</summary>
			/// <returns>
			/// 現在のカーソル座標を””Vector2””で返す	</returns>
			static Vector2 GetCursorPosition();

			/// <summary>
			/// マウスが押された瞬間かどうかを取得する	</summary>
			/// <param name = "_mb">
			/// ／取得したいマウスのボタン名	</param>
			/// <returns>
			/// 押された瞬間なら""true""、それ以外は""false""を返す	</returns>
			static bool GetMouseDown_Trigger(MouseButtonName _mb);
			/// <summary>
			/// マウスが押されているかどうかを取得する	</summary>
			/// <param name = "_mb">
			/// ／取得したいマウスのボタン名	</param>
			/// <returns>
			/// 押されているなら""true""、それ以外は""false""を返す	</returns>
			static bool GetMouseDown(MouseButtonName _mb);
			
			/// <summary>
			/// マウスホイールが回転されているかどうかを取得する	</summary>
			/// <returns>
			/// 回転されているなら""true""、それ以外は""false""を返す	</returns>
			static bool GetWheelRotation();

			/// <summary>
			/// マウスホイールが前方回転されているかどうかを取得する	</summary>
			/// <returns>
			/// 前方回転されているなら""true""、それ以外は""false""を返す	</returns>
			static bool GetWheelRotation_Forward();

			/// <summary>
			/// マウスホイールが後方回転されているかどうかを取得する	</summary>
			/// <returns>
			/// 後方回転されているなら""true""、それ以外は""false""を返す	</returns>
			static bool GetWheelRotation_Backward();
	};
}

