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
		public:
			// ----- functions / �֐� ----- //
			void Init()
			{
				// ===== �G�f�B�b�g�p�J�����̐��� ===== //
				AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
				
				// ===== �}�j�s�����[�^�[�p�I�u�W�F�N�g�̐��� ===== //
				// ----- �ړ��n ----- //
				AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");	// X�����ւ̈ړ�
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveY");	// Y�����ւ̈ړ�
				//AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveZ");	// Z�����ւ̈ړ�
			}
	};
};

