#pragma once
/**
* @file		SystemSceneManager.h
* @brief	SystemSceneManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SceneBase.h"
#include "LaunchSceneInformation.h"

#include <string>
#include <unordered_map>


namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			/// �V�[���Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
			class SystemSceneManager
			{
				private:
					// ----- variables / �ϐ� ----- //
					/// <summary>
					///	�G�f�B�b�g�p�V�[��	</summary>
					static SceneBase* m_editScene;
					/// <summary>
					///	�N������V�[�����	</summary>
					static Ctlan::PrivateSystem::Information::LaunchSceneInformation m_launchSceneInfo;
					/// <summary>
					///	�Z�[�u���邩�ǂ���	</summary>
					static bool isSave;

					// ----- functions / �֐� ----- //
					/// <summary>
					///	���݂̃V�[����Ԃ��Z�[�u	</summary>
					static void SaveSceneData();
					/// <summary>
					/// �V�[���̃��[�h	</summary>
					static void LoadScene();

				protected:
					// ----- variables / �ϐ� ----- //
					/// <summary>
					///	���݃��[�h����Ă���V�[��	</summary>
					static SceneBase* m_loadedScene;
					/// <summary>
					///	�V�[���ꗗ	</summary>
					static std::unordered_map<std::string, SceneBase*> m_scenePool;

					// ----- functions / �֐� ----- //
					/// <summary>
					///	�V�[���������[�h	</summary>
					/// <param name="loadSceneName">
					///	���[�h����V�[����	</param>
					/// <returns>
					/// ���[�h����V�[��������΃V�[�����A�������nullptr	</returns>
					static SceneBase* LoadSceneData(const char* loadSceneName);

				public:
					// ----- functions / �֐� ----- //
					/// <summary>
					///	�R���X�g���N�^	</summary>
					SystemSceneManager();
					/// <summary>
					///	�f�X�g���N�^	</summary>
					virtual ~SystemSceneManager() {};

					//**  �V�[���S�ʂɊւ�鏈��  **//	
					/// <summary>
					/// ���݃V�[���̏���������	</summary>
					static void InitScene();
					/// <summary>
					///	���݃V�[���̏I������	</summary>
					static void UninitScene();
					/// <summary>
					///	���݃V�[���̍X�V����	</summary>
					static void UpdateScene();
					/// <summary>
					///	���݃V�[���̕`�揈��	</summary>
					static void DrawScene();

					static void SaveScene() { isSave = true; };

					/// <summary>
					///	�V�K�V�[�����쐬	</summary>
					/// <param name="sceneName">
					///	�V�K�V�[����	</param>
					static void CreateNewScene(const char* sceneName);
					/// <summary>
					///	�G�f�B�b�g�V�[�����擾	</summary>
					/// <returns>
					///	�G�f�B�b�g�V�[�����	</returns>
					static SceneBase* GetEditScene() { return m_editScene; };
			};
		}

	}
}
