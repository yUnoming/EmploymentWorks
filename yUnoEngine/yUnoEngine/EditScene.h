#pragma once
/**
* @file		EditScene.h
* @brief	EditScene�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.12.25
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SceneBase.h"

#include "SpectatorCamera.h"
#include "Manipulator_MoveX.h"


namespace yUnoEngine
{
	/// <summary>
	///	�G�f�B�b�g�V�[��	</summary>
	class EditScene : public SceneBase
	{
		private:
			/// <summary>
			///	�G�f�B�b�g���Ɏg�p����J����	</summary>
			SpectatorCamera* m_spectatorCamera;
			/// <summary>
			///	X�����ւ̈ړ��}�j�s�����[�^�[	</summary>
			Manipulator::Manipulator_MoveX* m_manipulator_MoveX;

		public:
			// ----- functions / �֐� ----- //
			void Init()
			{
				// ===== �G�f�B�b�g�p�J�����̐��� ===== //
				m_spectatorCamera = AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
				
				// ===== �}�j�s�����[�^�[�p�I�u�W�F�N�g�̐��� ===== //
				// ----- �ړ��n ----- //
				m_manipulator_MoveX = AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveY");
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveZ");
			}

			void Update()
			{
				// �I�u�W�F�N�g���N���b�N�����H
				if (m_spectatorCamera->GetClickedObject() != nullptr)
				{
					// ===== �}�j�s�����[�^�[�̕\������ ===== //
					m_manipulator_MoveX->isActive = true;
					m_manipulator_MoveX->transform->parent = m_spectatorCamera->GetClickedObject();
				}
				else
				{
					// ===== �}�j�s�����[�^�[�̔�\������ ===== //
					m_manipulator_MoveX->isActive = false;
					m_manipulator_MoveX->transform->parent = nullptr;
				}

				SceneBase::Update();
			}
	};
};

