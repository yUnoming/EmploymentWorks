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
#include "GameObject.h"
#include "modelRenderer.h"
#include "Material.h"
#include "Transform.h"

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
		class Manipulator_MoveX : public GameObject
		{
			public :
				void Init()
				{
					AddComponent<ModelRenderer>()->Load("Assets/Models\\test2.obj");
					Material *mat = AddComponent<Material>();
					mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);

					transform->position.z = 5.0f;
				};

				void Update()
				{

				};
		};
	}
}


