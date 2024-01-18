#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "Material.h"


using namespace PublicSystem;


class Test : public GameObject
{
	public:
		/// <summary>
		///	�R���X�g���N�^	</summary>
		Test() : GameObject() {};
		/// <summary>
		///	�����t���R���X�g���N�^	</summary>
		/// <param name="nowScene">
		///	�I�u�W�F�N�g���������ꂽ�V�[��	</param>
		Test(SceneBase* nowScene) : GameObject(nowScene) {};

		void Init()
		{
			AddComponent<ModelRenderer>()->Load("Assets/Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();
			AddComponent<Material>()->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);

			transform->position.x = 0.0f;
			transform->position.z = 3.0f;
		}
};

