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
#include <list>
#include <array>
#include <vector>
#include "GameObject.h"

/// <summary>
/// �V�[���Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
class yUno_SceneManager
{
	private :
		// ----- variables / �ϐ� ----- //
		/// <summary>
		///	�V�[����	</summary>
		char* m_sceneName;

		// ----- functions / �֐� ----- //
		/// <summary>
		///	���݂̃V�[����Ԃ��Z�[�u	</summary>
		void SaveSceneData();
		/// <summary>
		///	�V�[���������[�h	</summary>
		/// <param name="loadSceneName">
		///	���[�h����V�[����	</param>
		void LoadSceneData(const char* loadSceneName);		

	protected:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		/// �V�[�����̃I�u�W�F�N�g	</summary>
		static std::array<std::list<GameObject*>, 4> m_sceneObject;

		/// <summary>
		///	���[�h���ꂽ�V�[��	</summary>
		static yUno_SceneManager* m_loadedScene;

	public:
		// ----- functions / �֐� ----- //
		/// <summary>
		///	�R���X�g���N�^	</summary>
		yUno_SceneManager();
		/// <summary>
		///	�f�X�g���N�^	</summary>
		virtual ~yUno_SceneManager() {};

		//**  �V�[���P�̂Ɋւ�鏈��  **//	
		/// <summary>
		///	������	</summary>
		virtual void Init() {};
		/// <summary>
		///	�I��	</summary>
		virtual void UnInit() {};
		/// <summary>
		///	�X�V	</summary>
		virtual void Update() {};
		/// <summary>
		///	�`��	</summary>
		virtual void Draw() {};

		//**  �V�[���S�ʂɊւ�鏈��  **//	
		/// <summary>
		/// �x�[�X�̏���������	</summary>
		void InitBase();
		/// <summary>
		///	�x�[�X�̏I������	</summary>
		void UnInitBase();
		/// <summary>
		///	�x�[�X�̍X�V����	</summary>
		void UpdateBase();
		/// <summary>
		///	�x�[�X�̕`�揈��	</summary>
		void DrawBase();

		//**  �V�[���֌W  **//
		/// <summary>
		/// �I�������V�[�������[�h	</summary>
		/// <param name="LoadScene&lt;&gt;();">
		/// &lt;&gt;���Ƀ��[�h����V�[�����L�q		</param>
		/// <returns>
		/// ���[�h�����V�[�� </returns>
		template<class T>
		T* LoadScene()
		{
			// ���݁A�V�[�����J���Ă���H
			if (m_loadedScene)
			{
				m_loadedScene->UnInitBase();		// �V�[���̏I������
				delete m_loadedScene;				// �V�[���̍폜
			}
			else
			{
				LoadSceneData(typeid(T).name());	// �G���W���J�n���̃V�[�����[�h
			}
			
			m_loadedScene = new T();				// �V���ȃV�[���̐���
			m_loadedScene->InitBase();				// �V���ȃV�[���̏�����
			m_sceneName =
				const_cast<char*>(typeid(T).name());// �V�K�V�[������ۑ�

			return (T*)m_loadedScene;
		}

		//**  �I�u�W�F�N�g�֌W  **//
		/// <summary>
		/// �V�[���ɑ��݂���I�u�W�F�N�g�����[�h	</summary>
		/// <param name="LoadSceneObject&lt;&gt;();">
		/// &lt;&gt;���Ƀ��[�h����I�u�W�F�N�g���L�q		</param>
		/// <param name="layer">
		///	���C���[�ԍ�	</param>
		/// <param name="name">
		///	���[�h����I�u�W�F�N�g�̖���	</param>
		/// <returns>
		/// ���[�h�����I�u�W�F�N�g </returns>
		template<class T>
		T* LoadSceneObject(int layer, const char* name)
		{
			T* obj = new T();						// �I�u�W�F�N�g�𐶐�
			obj->CopyName(name);					// �I�u�W�F�N�g����ݒ�
			m_sceneObject[layer].push_back(obj);	// �w�肳�ꂽ�v�f�ʒu�ɕۑ�
			obj->Init();							// �I�u�W�F�N�g�̏�����

			// ���������I�u�W�F�N�g��Ԃ�
			return obj;
		}
		/// <summary>
		/// �V�[���ɃI�u�W�F�N�g��ǉ�	</summary>
		/// <param name="AddSceneObject&lt;&gt;();">
		/// &lt;&gt;���ɒǉ�����I�u�W�F�N�g���L�q		</param>
		/// <param name="layer">
		///	���C���[�ԍ�	</param>
		/// <param name="name">
		///	�ǉ�����I�u�W�F�N�g�̖���	</param>
		/// <returns>
		/// �ǉ������I�u�W�F�N�g </returns>
		template<class T>
		T* AddSceneObject(int layer, const char* name)
		{
			T* obj = new T();						// �I�u�W�F�N�g�𐶐�
			obj->SetName(name);						// �I�u�W�F�N�g����ݒ�
			m_sceneObject[layer].push_back(obj);	// �w�肳�ꂽ�v�f�ʒu�ɕۑ�
			obj->Init();							// �I�u�W�F�N�g�̏�����

			// ���������I�u�W�F�N�g��Ԃ�
			return obj;
		}
		/// <summary>
		/// �V�[������I�u�W�F�N�g���擾	</summary>
		/// <param name="GetSceneObject&lt;&gt;();">
		/// &lt;&gt;���Ɏ擾����I�u�W�F�N�g�����L�q		</param>
		/// <param name="name">
		///	�擾����I�u�W�F�N�g�̖���	</param>
		/// <returns>
		/// �擾�����I�u�W�F�N�g�A�������nullptr </returns>
		template<class T> T* GetSceneObject(const char* name)
		{
			// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
			for (auto& objectList : m_sceneObject)
			{
				// ���X�g���̃I�u�W�F�N�g�擾
				for (GameObject* object : objectList)
				{
					if (typeid(*object) == typeid(T) && strcmp(object->GetName(), name) == 0)
					{
						return (T*)object;
					}
				}
			}

			return nullptr;
		}

		/// <summary>
		///	�V�[������I�u�W�F�N�g���擾	</summary>
		/// <param name="name">
		/// �擾����I�u�W�F�N�g�̖���	</param>
		/// <returns>
		/// �擾�����I�u�W�F�N�g�A�������nullptr </returns>
		GameObject* GetSceneObject(const char* name)
		{
			// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
			for (auto& objectList : m_sceneObject)
			{
				// ���X�g���̃I�u�W�F�N�g�擾
				for (GameObject* object : objectList)
				{
					if (strcmp(object->GetName(), name) == 0)
					{
						return object;
					}
				}
			}

			return nullptr;
		}
		/// <summary>
		/// ���݃V�[���ɑ��݂���I�u�W�F�N�g��S�擾
		/// </summary>
		/// <returns>
		///	�S�I�u�W�F�N�g�����������X�g	</returns>
		template<class T>
		std::array<std::list<GameObject*>, 4> GetAllSceneObjects()
		{
			return m_sceneObject;
		}
};
