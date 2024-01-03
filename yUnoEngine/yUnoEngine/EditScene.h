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
#include "Manipulator_MoveY.h"
#include "Manipulator_MoveZ.h"


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
			/// <summary>
			///	Y�����ւ̈ړ��}�j�s�����[�^�[	</summary>
			Manipulator::Manipulator_MoveY* m_manipulator_MoveY;
			/// <summary>
			///	Z�����ւ̈ړ��}�j�s�����[�^�[	</summary>
			Manipulator::Manipulator_MoveZ* m_manipulator_MoveZ;

		public:
			// ----- functions / �֐� ----- //
			void Init()
			{
				// ===== �G�f�B�b�g�p�J�����̐��� ===== //
				m_spectatorCamera = AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
				
				// ===== �}�j�s�����[�^�[�p�I�u�W�F�N�g�̐��� ===== //
				// ----- �ړ� ----- //
				m_manipulator_MoveX = AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");
				m_manipulator_MoveY = AddSceneObject<Manipulator::Manipulator_MoveY>(1, "Manipulator_MoveY");
				m_manipulator_MoveZ = AddSceneObject<Manipulator::Manipulator_MoveZ>(1, "Manipulator_MoveZ");
			}

			void Update()
			{
				// �I�u�W�F�N�g���N���b�N�����H
				if (m_spectatorCamera->GetClickedObject() != nullptr)
				{
					// ===== �}�j�s�����[�^�[�̕\������ ===== //
					// ----- �ړ� ----- //
					// X������
					m_manipulator_MoveX->isActive = true;
					m_manipulator_MoveX->transform->parent = m_spectatorCamera->GetClickedObject();
					// Y������
					m_manipulator_MoveY->isActive = true;
					m_manipulator_MoveY->transform->parent = m_spectatorCamera->GetClickedObject();
					// Z������
					m_manipulator_MoveZ->isActive = true;
					m_manipulator_MoveZ->transform->parent = m_spectatorCamera->GetClickedObject();
				}
				else
				{
					// ===== �}�j�s�����[�^�[�̔�\������ ===== //
					// ----- �ړ� ----- //
					// X������
					m_manipulator_MoveX->isActive = false;
					m_manipulator_MoveX->transform->parent = nullptr;
					// Y������
					m_manipulator_MoveY->isActive = false;
					m_manipulator_MoveY->transform->parent = nullptr;
					// Z������
					m_manipulator_MoveZ->isActive = false;
					m_manipulator_MoveZ->transform->parent = nullptr;
				}

				// �V�[���̊�{�I�ȍX�V���������s
				SceneBase::Update();
			}
	};
};

