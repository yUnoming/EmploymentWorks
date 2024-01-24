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
namespace Ctlan
{
	namespace EngineObject
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
					// ���W�A���p�ɒ���
					float rotY = spectatorCamera->transform->rotation.y * 3.14f / 180.0f;
					// �}�E�X�̍��W�����Ɉړ��ʂ��v�Z
					float addX = sinf(rotY) * (lateCursorPos.x - nowCursorPos.x) * 0.01f;
					float addY = cosf(rotY) * (lateCursorPos.y - nowCursorPos.y) * 0.01f;

					// Z���W�����֐e�I�u�W�F�N�g���ړ�
					transform->parent->transform->position.z += addX + addY;
				}
			};
		}
	}
}