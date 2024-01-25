#pragma once
/**
* @file		SystemMouseInputManager.h
* @brief	SystemMouseInputManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.07
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "InputPartsName.h"
#include "Vector2.h"

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	マウス入力を判定するための処理を管理するクラス	</summary>
			class SystemMouseInputManager
			{
				private:
					/// <summary>
					///	マウスの状態	</summary>
					enum MouseStatus
					{
						/// <summary>
						///	まだ押されていない／判定超過	</summary>
						NoStatus,
						/// <summary>
						/// 離されている		</summary>
						Up,
						/// <summary>
						///	押されている	</summary>
						Down
					};
					/// <summary>
					///	マウスホイールの状態	</summary>
					enum MouseWheelStatus
					{
						ForwardRotation,	// 前方回転
						BackwardRotation,	// 後方回転
						NotRotation			// 回転していない
					};

					// ----- variables / 変数 ----- //
					/// <summary>
					///	現在のマウスの状態	</summary>
					static MouseStatus m_nowMouseState[3];
					/// <summary>
					/// 前回のマウスの状態	</summary>
					static MouseStatus m_lateMouseState[3];
					/// <summary>
					/// マウスホイールの入力値
					/// 正の値：前方に回転
					/// 負の値：後方に回転	</summary>
					static MouseWheelStatus m_mouseWheelState;

					/// <summary>
					///	前回のカーソル座標	</summary>
					static PublicSystem::Vector2 m_lateCursorPosition;
					/// <summary>
					///	現在のカーソル座標	</summary>
					static PublicSystem::Vector2 m_nowCursorPosition;

				public:
					// ----- functions / 関数 ----- //
					/// <summary>
					///	更新処理	</summary>
					static void Update();

					/// <summary>
					///	前回のカーソル座標を取得	</summary>
					/// <returns>
					///	前回のカーソル座標	</returns>
					static PublicSystem::Vector2 GetLateCursorPosition() { return m_lateCursorPosition; };
					/// <summary>
					/// 現在のカーソル座標を取得	</summary>
					/// <returns>
					///	現在のカーソル座標	</returns>
					static PublicSystem::Vector2 GetNowCursorPosition() { return m_nowCursorPosition; };

					/// <summary>
					/// 現在のマウスの状態を保存	</summary>
					static void KeepNowMouseState();
					/// <summary>
					/// マウスが押されたことをセット	</summary>
					/// <param name = "button">
					/// 押されたマウスのボタン名	</param>
					static void SetMouseDown(Ctlan::PublicSystem::MouseButtonName button);
					/// <summary>
					/// マウスが離されたことをセット
					/// </summary>
					/// <param name = "button">
					/// 離されたマウスのボタン名</param>
					static void SetMouseUp(Ctlan::PublicSystem::MouseButtonName button);
					/// <summary>
					/// マウスホイールの状態をセット	</summary>
					/// <param name="mouseWheelParam">
					/// マウスホイールの入力値	</param>
					static void SetMouseWheelState(int mouseWheelParam);

					/// <summary>
					/// マウスが押された瞬間かどうかを判定	</summary>
					/// <param name = "button">
					/// 判定するマウスのボタン名	</param>
					/// <returns>
					/// 押された瞬間ならtrue、それ以外ならfalse	</returns>
					static bool GetMouseDownTrigger(Ctlan::PublicSystem::MouseButtonName button);
					/// <summary>
					/// マウスが押されているかどうかを判定	</summary>
					/// <param name = "button">
					/// 判定するマウスのボタン名	</param>
					/// <returns>
					/// 押されているならtrue、それ以外ならfalse	</returns>
					static bool GetMouseDown(Ctlan::PublicSystem::MouseButtonName button);

					/// <summary>
					///	マウスが離された瞬間かどうかを判定	</summary>
					/// <param name="button">
					///	判定するマウスのボタン名	</param>
					/// <returns>
					///	離された瞬間ならtrue、それ以外ならfalse	</returns>
					static bool GetMouseUpTrigger(Ctlan::PublicSystem::MouseButtonName button);
					/// <summary>
					///	マウスが離されているかどうかを判定	</summary>
					/// <param name="button">
					///	判定するマウスのボタン名	</param>
					/// <returns>
					///	離されているならtrue、それ以外ならfalse	</returns>
					static bool GetMouseUp(Ctlan::PublicSystem::MouseButtonName button);

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
	}
}

