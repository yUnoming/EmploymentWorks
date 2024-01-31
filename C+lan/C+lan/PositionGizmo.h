#pragma once
/**
* @file		PositionGizmo.h
* @brief	PositionGizmo�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.31
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "modelRenderer.h"
#include "Material.h"
#include "Transform.h"

#include "MouseInput.h"
#include "SpectatorCamera.h"

#include "SystemSceneManager.h"


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
			///	Transform��Position�p�M�Y���̐e�I�u�W�F�N�g	</summary>
			class PositionGizmo : public Ctlan::PrivateSystem::GameObject
			{
				protected:
					/// <summary>
					///	�G�f�B�b�g�J����	</summary>
					EngineObject::SpectatorCamera* spectatorCamera;
					/// <summary>
					///	���݂̃J�[�\���ʒu	</summary>
					Vector2 nowCursorPos;
					/// <summary>
					///	�O��̃J�[�\���ʒu	</summary>
					Vector2 lateCursorPos;
					/// <summary>
					///	�N���b�N���ꂽ���ǂ���	</summary>
					bool isClicked = false;
					/// <summary>
					///	�}�e���A���R���|�[�l���g	</summary>
					Material* mat;

				public:
					/// <summary>
					///	�R���X�g���N�^	</summary>
					PositionGizmo() : GameObject()
					{
						// �}�e���A���ǉ�
						mat = AddComponent<Material>();
						// ���f���ǉ�
						AddComponent<Ctlan::PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\PositionGizmo.obj");
						// �G�f�B�b�g�J�����擾
						spectatorCamera = Ctlan::PrivateSystem::SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject<EngineObject::SpectatorCamera>("SpectatorCamera");
						// �T�C�Y����
						transform->scale *= 0.7f;
						// ��\���ɂ��Ă���
						isActive = false;
					};
					/// <summary>
					///	�����t���R���X�g���N�^	</summary>
					/// <param name="nowScene">
					///	�I�u�W�F�N�g���������ꂽ�V�[��	</param>
					PositionGizmo(SceneBase* nowScene) : GameObject(nowScene)
					{
						// �}�e���A���ǉ�
						mat = AddComponent<Material>();
						// ���f���ǉ�
						AddComponent<Ctlan::PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\PositionGizmo.obj");
						// �G�f�B�b�g�J�����擾
						spectatorCamera = Ctlan::PrivateSystem::SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject<EngineObject::SpectatorCamera>("SpectatorCamera");
						// �T�C�Y����
						transform->scale *= 0.7f;
						// ��\���ɂ��Ă���
						isActive = false;
					};


					void Update() override
					{
						// ���g���N���b�N����Ă���H
						if (spectatorCamera->GetClickedManipulator() == this)
						{
							// ���݂̃J�[�\���ʒu���擾
							nowCursorPos = Ctlan::PublicSystem::MouseInput::GetCursorPosition();
							// �N���b�N����Ă���H
							if (isClicked)
							{
								ClickAction();	// �N���b�N���ꂽ�ۂ̏��������s
							}

							isClicked = true;				// �N���b�N����Ă����Ԃɐ؂�ւ�
							lateCursorPos = nowCursorPos;	// ���݂̃J�[�\���ʒu��ۑ�
						}
						// �O��܂ŃN���b�N����Ă����H
						else if (isClicked)
						{
							isClicked = false;	// �N���b�N����Ă��Ȃ���Ԃɐ؂�ւ�
						}
					};
					/// <summary>
					///	�N���b�N���ꂽ�ۂ̃A�N�V����	</summary>
					virtual void ClickAction() {};
			};
		}
	}
}

