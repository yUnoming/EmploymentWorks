#pragma once
/**
* @file		PositionXGizmo.h
* @brief	PositionXGizmo�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.24
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "PositionGizmo.h"


/// <summary>
///	�G���W���Q	</summary>
namespace Ctlan
{
	namespace EngineObject
	{
		/// <summary>
		///	�M�Y���Q	</summary>
		namespace Gizmo
		{
			/// <summary>
			///	X���ړ��M�Y��	</summary>
			class PositionXGizmo : public PositionGizmo
			{
				public:
					PositionXGizmo(SceneBase* nowScene) : PositionGizmo(nowScene) {};

					void Init()
					{
						// �}�e���A���J���[�ύX
						mat->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);
						transform->rotation.z = -90.0f;
					};

					void ClickAction()
					{
						// ���W�A���p�ɒ���
						float rotY = spectatorCamera->transform->rotation.y * 3.14f / 180.0f;
						// �}�E�X�̍��W�����Ɉړ��ʂ��v�Z
						float addX = cosf(rotY) * (lateCursorPos.x - nowCursorPos.x) * -0.01f;
						float addY = sinf(rotY) * (lateCursorPos.y - nowCursorPos.y) * 0.01f;

						// X���W�����֐e�I�u�W�F�N�g���ړ�
						transform->parent->transform->position.x += addX + addY;
					}
			};
		}

	}
}


