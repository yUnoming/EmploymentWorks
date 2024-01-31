#pragma once
/**
* @file		TemplateText.h
* @brief	TemplateText�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.01.18
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Text.h"
#include "Shader.h"


namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	�쐬�^�u�ō쐬�ł���e�L�X�g	</summary>
		class TemplateText : public PrivateSystem::GameObject
		{
			public:
				/// <summary>
				///	�R���X�g���N�^	</summary>
				TemplateText() : GameObject()
				{
					GetComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\unlitTextureVS.cso", "Assets\\Shaders\\unlitTexturePS.cso");
					AddComponent<Material>();
					Text* textComponent = AddComponent<Text>();
					textComponent->text = "Input text";
					textComponent->fontSize = Vector2(20, 30);

					transform->position.x = 0.0f;
					transform->position.z = 3.0f;
				};
				/// <summary>
				///	�����t���R���X�g���N�^	</summary>
				/// <param name="nowScene">
				///	�I�u�W�F�N�g���������ꂽ�V�[��	</param>
				TemplateText(SceneBase* nowScene) : GameObject(nowScene)
				{
					GetComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\unlitTextureVS.cso", "Assets\\Shaders\\unlitTexturePS.cso");
					AddComponent<Material>();
					Text* textComponent = AddComponent<Text>();
					textComponent->text = "Input text...";
					textComponent->fontSize = Vector2(20, 30);

					transform->position.x = 0.0f;
					transform->position.z = 3.0f;
				};
		};
	}
}

