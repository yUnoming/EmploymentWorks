#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "InputPartsName.h"
#include "Material.h"
#include "Text.h"
#include "Shader.h"

using namespace PublicSystem;


class Test2 : public GameObject
{
	public:
		/// <summary>
		///	�R���X�g���N�^	</summary>
		Test2() : GameObject() {};
		/// <summary>
		///	�����t���R���X�g���N�^	</summary>
		/// <param name="nowScene">
		///	�I�u�W�F�N�g���������ꂽ�V�[��	</param>
		Test2(SceneBase* nowScene) : GameObject(nowScene) {};

		void Init()
		{
			GetComponent<PublicSystem::Shader>()->Load("Assets\\Shaders\\unlitTextureVS.cso", "Assets\\Shaders\\unlitTexturePS.cso");
			Material mat;
			AddComponent<Material>();

			transform->position.x = 0.0f;
			transform->position.z = 3.0f;
			Text* textComponent = AddComponent<Text>();
			textComponent->text = "Input text...";
			textComponent->fontSize = Vector2(20, 30);
		}
};

