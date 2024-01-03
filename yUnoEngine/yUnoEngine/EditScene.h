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

#include "Camera.h"


namespace yUnoEngine
{
	/// <summary>
	///	�G�f�B�b�g�V�[��	</summary>
	class EditScene : public SceneBase
	{
		private:
			// ----- structs / �\���� ----- //
			
			/// <summary>
			///	�V�[���ҏW���Ɏg���f�[�^	</summary>
			struct SceneEditorData
			{
				/// <summary>
				///	�ҏW���Ɏg�p����J�����̃R���|�[�l���g���	</summary>
				Transform transformComponent;	// �g�����X�t�H�[��
				Camera cameraComponent;			// �J����

				/// <summary>
				///	���[�h����V�[����	</summary>
				char loadSceneName[30];
			};
			
			// ----- variables / �ϐ� ----- //
			/// <summary>
			///	�V�[���ҏW�Ɏg�p����f�[�^	</summary>
			SceneEditorData m_sceneEditorData;
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
			void Init() override;
			void UnInit() override;
			void Update() override;
	};
};

