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
#include "GameObject.h"

/// <summary>
/// �V�[���Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
class yUno_SceneManager
{
	protected:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		/// �V�[�����̃I�u�W�F�N�g	</summary>
		static std::array<std::list<GameObject*>, 4> m_sceneObject;

		/// <summary>
		///	���[�h���ꂽ�V�[��	</summary>
		yUno_SceneManager* m_loadedScene;

	public:
		// ----- functions / �֐� ----- //
		/// <summary>
		///	�R���X�g���N�^	</summary>
		yUno_SceneManager() : m_loadedScene(nullptr) {}
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
		template<class T> T* LoadScene();


		//**  �I�u�W�F�N�g�֌W  **//
		/// <summary>
		/// �V�[���ɃI�u�W�F�N�g��ǉ�	</summary>
		/// <param name="AddObject&lt;&gt;();">
		/// &lt;&gt;���ɒǉ�����I�u�W�F�N�g���L�q		</param>
		/// <param name="layer">
		///	���C���[�ԍ�	</param>
		/// <returns>
		/// �ǉ������I�u�W�F�N�g </returns>
		template<class T> T* AddSceneObject(int layer);
		/// <summary>
		/// �V�[������I�u�W�F�N�g���擾	</summary>
		/// <param name="GetObject&lt;&gt;();">
		/// &lt;&gt;���Ɏ擾����I�u�W�F�N�g�����L�q		</param>
		/// <returns>
		/// �擾�����I�u�W�F�N�g </returns>
		template<class T> T* GetSceneObject();
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

template<class T> 
T* yUno_SceneManager::LoadScene()
{
	// ���݁A�V�[�����J���Ă���H
	if (m_loadedScene)
	{
		m_loadedScene->UnInitBase();	// �V�[���̏I������
		delete m_loadedScene;			// �V�[���̍폜
	}

	m_loadedScene = new T();	// �V���ȃV�[���̐���
	m_loadedScene->InitBase();	// �V���ȃV�[���̏�����

	return (T*)m_loadedScene;
}

template<class T>
T* yUno_SceneManager::AddSceneObject(int layer)
{
	T* obj = new T();						// �I�u�W�F�N�g�𐶐�
	m_sceneObject[layer].push_back(obj);	// �w�肳�ꂽ�v�f�ʒu�ɕۑ�
	obj->Init();							// �I�u�W�F�N�g�̏�����

	// ���������I�u�W�F�N�g��Ԃ�
	return obj;
}

template<class T>
T* yUno_SceneManager::GetSceneObject()
{
	for (auto& objectList : m_sceneObject)
	{
		for (GameObject* object : objectList)
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
	}

	return nullptr;
}