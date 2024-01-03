#pragma once
/**
* @file		Manipulator_MoveX.h
* @brief	Manipulator_MoveXクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.12.24
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
		///	X座標方向の移動マニピュレーター	</summary>
		class Manipulator_MoveX : public Manipulator
		{
			public :
				void Init()
				{
					Material *mat = AddComponent<Material>();
					mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
					//transform->rotation.z = -90.0f;
				};

				void ClickAction()
				{
					transform->parent->transform->position.y += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
				}
		};
	}
}


