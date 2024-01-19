#pragma once
/**
* @file		TemplateCube.h
* @brief	TemplateCube�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.01.18
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "Material.h"


// ������������������������������ //
// �@�@		 using�錾 		�@�@  //
// ������������������������������ //
using namespace PublicSystem;


namespace EngineObject
{
	class TemplateCube : public GameObject
	{
	public:
		/// <summary>
		///	�R���X�g���N�^	</summary>
		TemplateCube() : GameObject()
		{
			AddComponent<ModelRenderer>()->Load("Assets/Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();
			AddComponent<Material>();

			transform->position.x = 0.0f;
			transform->position.z = 3.0f;
		};
		/// <summary>
		///	�����t���R���X�g���N�^	</summary>
		/// <param name="nowScene">
		///	�I�u�W�F�N�g���������ꂽ�V�[��	</param>
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

