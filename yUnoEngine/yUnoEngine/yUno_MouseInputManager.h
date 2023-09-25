#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"


namespace yUno_SystemManager
{
	// マウスの状態
	enum MOUSE_STATUS
	{
		NOSTATUS,	// まだ押されていない or 判定超過
		UP,			// キーが離されている
		DOWN,		// キーが押されている
	};

	// マウスホイールの状態
	enum MOUSEWHEEL_STATUS
	{
		FORWARD_ROTATION,	// 前方回転
		BACKWARD_ROTATION,	// 後方回転
		NOT_ROTATION,		// 回転していない
	};

	class yUno_MouseInputManager
	{
		public:
			// ----- variables / 変数 ----- //

			// 現在のマウスの状態
			static MOUSE_STATUS Now_Mouse_Status[3];

			// 前回のマウスの状態
			static MOUSE_STATUS Late_Mouse_Status[3];

			// マウスホイールの入力値
			// 正の値：前方に回転
			// 負の値：後方に回転
			static MOUSEWHEEL_STATUS MouseWheel_Status;

			// ----- functions / 関数 ----- //
			/// <summary>
			/// 現在のマウスの状態を保存する
			/// </summary>
			static void Keep_Now_MouseStatus();
			/// <summary>
			/// マウスが押されたことをセットする
			/// </summary>
			/// <param name = "_mb">／セットしたいマウスのボタン名</param>
			static void Set_MouseDown(PublicSystem::MouseButtonName _mb);
			/// <summary>
			/// マウスが離されたことをセットする関数
			/// </summary>
			/// <param name = "_mb">／セットしたいマウスのボタン名</param>
			static void Set_MouseUp(PublicSystem::MouseButtonName _mb);
			/// <summary>
			/// マウスホイールの入力値をセットする
			/// </summary>
			static void Set_MouseWheel_Status(int _wheelParam);

	};
}

