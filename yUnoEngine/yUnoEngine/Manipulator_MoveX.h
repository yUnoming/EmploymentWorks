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
namespace yUnoEngine
{
	/// <summary>
	///	�}�j�s�����[�^�[�Q	</summary>
	namespace Manipulator
	{
		/// <summary>
		///	X���W�����̈ړ��}�j�s�����[�^�[	</summary>
		class Manipulator_MoveX : public Manipulator
		{
			public :
				void Init()
				{
					Material *mat = AddComponent<Material>();
					mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
					//transform->rotation.z = -90.0f;
				};

				void ClickAction()
				{
					transform->parent->transform->position.y += (lateCursorPos.y - nowCursorPos.y) * 0.01f;
				}
		};
	}
}


