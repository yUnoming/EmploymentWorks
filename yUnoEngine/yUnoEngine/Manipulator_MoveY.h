#pragma once
/**
* @file		Manipulator_MoveY.h
* @brief	Manipulator_MoveYクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.31
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Manipulator.h"

/// <summary>
///	エンジン群	</summary>
namespace yUnoEngine
{
	/// <summary>
	///	マニピュレーター群	</summary>
	namespace Manipulator
	{
		/// <summary>
		///	Y座標方向の移動マニピュレーター	</summary>
		class Manipulator_MoveY : public Manipulator
		{
			void Init()
			{
				// マテリアル追加
				Material* mat = AddComponent<Material>();
				mat->materialColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
			};

			void ClickAction()
			{
				// Y座標方向へ親オブジェクトを移動
				transform->parent->transform->position.y += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
			}
		};
	}
}

