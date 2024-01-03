#pragma once
/**
* @file		Manipulator.h
* @brief	Manipulator�N���X�̃w�b�_�[�t�@�C��
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

#include "yUno_SceneManager.h"
#include "SceneManager.h"


/// <summary>
///	�G���W���Q	</summary>
namespace yUnoEngine
{
	/// <summary>
	///	�}�j�s�����[�^�[�Q	</summary>
	namespace Manipulator
	{
		class Manipulator :	public GameObject
		{
			protected:
				/// <summary>
				///	�G�f�B�b�g�J����	</summary>
				SpectatorCamera* spectatorCamera;
				/// <summary>
				///	���݂̃J�[�\���ʒu	</summary>
				Vector2 nowCursorPos;
				/// <summary>
				///	�O��̃J�[�\���ʒu	</summary>
				Vector2 lateCursorPos;
				/// <summary>
				///	�N���b�N���ꂽ���ǂ���	</summary>
				bool isClicked = false;

			public:
				/// <summary>
				///	�R���X�g���N�^	</summary>
				Manipulator() {
					AddComponent<ModelRenderer>()->Load("Assets/Models\\test2.obj");
					spectatorCamera = yUno_SceneManager::GetEditScene()->GetSceneObject<SpectatorCamera>("SpectatorCamera");
					isActive = false;
				};

				void Update() override
				{
					// ���g���N���b�N����Ă���H
					if (spectatorCamera->GetClickedManipulator() == this)
					{
						nowCursorPos = PublicSystem::MouseInput::GetCursorPosition();

						if (isClicked)
						{
							ClickAction();
						}

						isClicked = true;
						lateCursorPos = nowCursorPos;
					}
					else if (isClicked)
					{
						isClicked = false;
					}
				};
				/// <summary>
				///	�N���b�N���ꂽ�ۂ̃A�N�V����	</summary>
				virtual void ClickAction() {};
		};
	}
}

