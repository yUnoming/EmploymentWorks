#pragma once
/**
* @file		Manipulator_MoveX.h
* @brief	Manipulator_MoveX�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.24
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "modelRenderer.h"
#include "Material.h"
#include "Transform.h"

/// <summary>
///	�G���W���Q	</summary>
namespace yUnoEngine
{
	/// <summary>
	///	�}�j�s�����[�^�[�Q	</summary>
	namespace Manipulator
	{
		/// <summary>
		///	X���W�����̈ړ��}�j�s�����[�^�[	</summary>
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


