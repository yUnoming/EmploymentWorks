#pragma once
/**
* @file		Manipulator_MoveZ.h
* @brief	Manipulator_MoveZ�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2024.1.3
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Manipulator.h"


/// <summary>
///	�G���W���Q	</summary>
namespace yUnoEngine
{
	/// <summary>
	///	�}�j�s�����[�^�[�Q	</summary>
	namespace Manipulator
	{
		/// <summary>
		///	Z���W�����̈ړ��}�j�s�����[�^�[	</summary>
		class Manipulator_MoveZ : public Manipulator
		{
			public:
				Manipulator_MoveZ(SceneBase* nowScene) : Manipulator(nowScene) {};

				void Init()
				{
					// �}�e���A���ǉ�
					Material* mat = AddComponent<Material>();
					mat->materialColor = Color(0.0f, 0.0f, 1.0f, 1.0f);
					transform->rotation.x = 90.0f;
				};

				void ClickAction()
				{
					// Z���W�����֐e�I�u�W�F�N�g���ړ�
					transform->parent->transform->position.z += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
				}
		};
	}
}

