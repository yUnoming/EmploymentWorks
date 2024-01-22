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
#include "Manipulator.h"


/// <summary>
///	�G���W���Q	</summary>
namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	�}�j�s�����[�^�[�Q	</summary>
		namespace Manipulator
		{
			/// <summary>
			///	X���W�����̈ړ��}�j�s�����[�^�[	</summary>
			class Manipulator_MoveX : public Manipulator
			{
				public:
					Manipulator_MoveX(SceneBase* nowScene) : Manipulator(nowScene) {};

					void Init()
					{
						// �}�e���A���ǉ�
						Material* mat = AddComponent<Material>();
						mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
						transform->rotation.z = -90.0f;
					};

					void ClickAction()
					{
						// X���W�����֐e�I�u�W�F�N�g���ړ�
						transform->parent->transform->position.x -= (lateCursorPos.x - nowCursorPos.x) * 0.01f;
					}
			};
		}

	}
}

