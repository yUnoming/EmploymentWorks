#pragma once
/**
* @file		yUno_SceneManager.h
* @brief	yUno_SceneManager�N���X�̃w�b�_�[�t�@�C��
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


/// <summary>
/// �V�[���Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
class yUno_SceneManager
{
	private :
		// ----- variables / �ϐ� ----- //
		/// <summary>
		///	�G�f�B�b�g�p�V�[��	</summary>
		static SceneBase* m_editScene;
		/// <summary>
		///	�N������V�[�����	</summary>
		static yUnoEngine::Information::LaunchSceneInformation m_launchSceneInfo;

		// ----- functions / �֐� ----- //
		/// <summary>
		///	���݂̃V�[����Ԃ��Z�[�u	</summary>
		static void SaveSceneData();
		/// <summary>
		/// �I�������V�[�������[�h	</summary>
		/// <param name="LoadScene&lt;&gt;();">
		/// &lt;&gt;���Ƀ��[�h����V�[�����L�q		</param>
		/// <returns>
		/// ���[�h�����V�[�� </returns>
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
		yUno_SceneManager();
		/// <summary>
		///	�f�X�g���N�^	</summary>
		virtual ~yUno_SceneManager() {};

		//**  �V�[���S�ʂɊւ�鏈��  **//	
		/// <summary>
		/// ���݃V�[���̏���������	</summary>
		static void InitScene();
		/// <summary>
		///	���݃V�[���̏I������	</summary>
		static void UnInitScene();
		/// <summary>
		///	���݃V�[���̍X�V����	</summary>
		static void UpdateScene();
		/// <summary>
		///	���݃V�[���̕`�揈��	</summary>
		static void DrawScene();

		/// <summary>
		///	�V�K�V�[�����쐬	</summary>
		/// <param name="sceneName">
		///	�V�K�V�[����	</param>
		static void CreateNewScene(const char* sceneName);
#if _DEBUG
		static SceneBase* GetEditScene() { return m_editScene; };
#endif
};
