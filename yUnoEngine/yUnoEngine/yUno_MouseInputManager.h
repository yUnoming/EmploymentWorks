#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"


namespace yUno_SystemManager
{
	// マウスの状態
	enum MOUSE_STATE
	{
		NOSTATUS,	// まだ押されていない or 判定超過
		UP,			// キーが離されている
		DOWN,		// キーが押されている
	};

	class yUno_MouseInputManager
	{
		public:
			// ----- variables / 変数 ----- //
			/// <summary>
			/// 現在のマウスの状態
			/// </summary>
			static MOUSE_STATE Now_MouseStatus[3];
			/// <summary>
			/// 前回のマウスの状態
			/// </summary>
			static MOUSE_STATE Late_MouseStatus[3];

			// ----- functions / 関数 ----- //
			/// <summary>
			/// 現在のマウスの状態を保存するための関数
			/// </summary>
			static void Keep_Now_MouseStatus();

			/// <summary>
			/// マウスが押されたことをセットする関数
			/// </summary>
			static void Set_MouseDown(PublicSystem::MouseButtonName _mb);
			/// <summary>
			/// マウスが離されたことをセットする関数
			/// </summary>
			static void Set_MouseUp(PublicSystem::MouseButtonName _mb);
	};
}

