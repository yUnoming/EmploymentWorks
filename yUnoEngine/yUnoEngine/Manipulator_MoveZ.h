#pragma once
/**
* @file		Manipulator_MoveZ.h
* @brief	Manipulator_MoveZクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2024.1.3
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
		///	Z座標方向の移動マニピュレーター	</summary>
		class Manipulator_MoveZ : public Manipulator
		{
			public:
				Manipulator_MoveZ(SceneBase* nowScene) : Manipulator(nowScene) {};

				void Init()
				{
					// マテリアル追加
					Material* mat = AddComponent<Material>();
					mat->materialColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
					transform->rotation.x = 90.0f;
				};

				void ClickAction()
				{
					// Z座標方向へ親オブジェクトを移動
					transform->parent->transform->position.z += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
				}
		};
	}
}

