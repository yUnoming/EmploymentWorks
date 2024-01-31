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


namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	作成タブで作成できるキューブ	</summary>
		class TemplateCube : public Ctlan::PrivateSystem::GameObject
		{
			public:
				/// <summary>
				///	コンストラクタ	</summary>
				TemplateCube() : GameObject()
				{
					AddComponent<Material>();
					AddComponent<PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\templateCube.obj");
					AddComponent<BoxCollider>();

					transform->position.x = 0.0f;
					transform->position.z = 3.0f;
				};
				/// <summary>
				///	引数付きコンストラクタ	</summary>
				/// <param name="nowScene">
				///	オブジェクトが生成されたシーン	</param>
				TemplateCube(SceneBase* nowScene) : GameObject(nowScene)
				{
					AddComponent<Material>();
					AddComponent<PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\templateCube.obj");
					AddComponent<BoxCollider>();

					transform->position.x = 0.0f;
					transform->position.z = 3.0f;
				};
			};
	}
}

