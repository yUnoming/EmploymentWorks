#pragma once
/**
* @file		Manipulator_MoveY.h
* @brief	Manipulator_MoveY�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.31
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
		///	Y���W�����̈ړ��}�j�s�����[�^�[	</summary>
		class Manipulator_MoveY : public Manipulator
		{
			void Init()
			{
				// �}�e���A���ǉ�
				Material* mat = AddComponent<Material>();
				mat->materialColor = Color(0.0f, 1.0f, 0.0f, 1.0f);
			};

			void ClickAction()
			{
				// Y���W�����֐e�I�u�W�F�N�g���ړ�
				transform->parent->transform->position.y += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
			}
		};
	}
}

