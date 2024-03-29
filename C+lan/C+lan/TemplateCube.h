#pragma once
/**
* @file		TemplateCube.h
* @brief	TemplateCubeNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.01.18
*/
//  //
// @@t@CΜCN[h@@ //
//  //
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
		///	μ¬^uΕμ¬Ε«ιL[u	</summary>
		class TemplateCube : public Ctlan::PrivateSystem::GameObject
		{
			public:
				/// <summary>
				///	RXgN^	</summary>
				TemplateCube() : GameObject()
				{
					AddComponent<Material>();
					AddComponent<PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\templateCube.obj");
					AddComponent<BoxCollider>();

					transform->position.x = 0.0f;
					transform->position.z = 3.0f;
				};
				/// <summary>
				///	ψt«RXgN^	</summary>
				/// <param name="nowScene">
				///	IuWFNgͺΆ¬³κ½V[	</param>
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

