#pragma once
/**
* @file		TemplateCube.h
* @brief	TemplateCubeクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.01.18
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "Material.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 using宣言 		　　  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace PublicSystem;


namespace EngineObject
{
	class TemplateCube : public GameObject
	{
	public:
		/// <summary>
		///	コンストラクタ	</summary>
		TemplateCube() : GameObject()
		{
			AddComponent<ModelRenderer>()->Load("Assets/Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();
			AddComponent<Material>();

			transform->position.x = 0.0f;
			transform->position.z = 3.0f;
		};
		/// <summary>
		///	引数付きコンストラクタ	</summary>
		/// <param name="nowScene">
		///	オブジェクトが生成されたシーン	</param>
		TemplateCube(SceneBase* nowScene) : GameObject(nowScene)
		{
			AddComponent<ModelRenderer>()->Load("Assets/Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();
			AddComponent<Material>();

			transform->position.x = 0.0f;
			transform->position.z = 3.0f;
		};
	};
}

