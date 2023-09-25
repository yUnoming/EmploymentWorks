#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>
#include <array>
#include "GameObject.h"

namespace yUno_SceneManagement
{
	class yUno_SceneManager
	{
	protected:
		// ----- variables / �ϐ� ----- //
		// �V�[�����̃I�u�W�F�N�g
		static std::array<std::list<GameObject*>, 4> m_SceneObject;

		// ���[�h���ꂽ�V�[��
		yUno_SceneManager* m_LoadedScene;

	public:
		// ----- functions / �֐� ----- //
		yUno_SceneManager() : m_LoadedScene(nullptr) {}// �R���X�g���N�^
		virtual ~yUno_SceneManager() {};	// �f�X�g���N�^

		//**  �V�[���P�̂Ɋւ�鏈��  **//
		virtual void Init() {};		// ������
		virtual void UnInit() {};	// �I��
		virtual void Update() {};	// �X�V
		virtual void Draw() {};		// �`��

		//**  �V�[���S�ʂɊւ�鏈��  **//
		void InitBase();	// ������
		void UnInitBase();	// �I��
		void UpdateBase();	// �X�V
		void DrawBase();	// �`��

		//**  �V�[���֌W  **//
		/// <summary>
		/// �I�����ꂽ�V�[�������[�h
		/// </summary>
		template<class T> void LoadScene();

		//**  �I�u�W�F�N�g�֌W  **//
		/// <summary>
		/// �I�u�W�F�N�g��ǉ�
		/// </summary>
		template<class T> T* AddObject(int _layer);

		/// <summary>
		/// �I�u�W�F�N�g���擾
		/// </summary>
		template<class T> T* GetObject();

		/// <summary>
		/// ���݃V�[���ɑ��݂���I�u�W�F�N�g��S�擾
		/// </summary>
		template<class T> std::array<std::list<GameObject*>, 4> GetAllObjects();

	};

	template<class T>
	void yUno_SceneManager::LoadScene()
	{
		// ���݁A�V�[�����J���Ă���H
		if (m_LoadedScene)
		{
			m_LoadedScene->UnInitBase();	// �V�[���̏I������
			delete m_LoadedScene;			// �V�[���̍폜
		}

		m_LoadedScene = new T();	// �V���ȃV�[���̐���
		m_LoadedScene->InitBase();	// �V���ȃV�[���̏�����
	}

	template<class T>
	T* yUno_SceneManager::AddObject(int _layer)
	{
		T* obj = new T();						// �I�u�W�F�N�g�𐶐�
		m_SceneObject[_layer].push_back(obj);	// �w�肳�ꂽ�v�f�ʒu�ɕۑ�
		obj->Init();							// �I�u�W�F�N�g�̏�����

		// ���������I�u�W�F�N�g��Ԃ�
		return obj;
	}
	
	template<class T>
	T* yUno_SceneManager::GetObject()
	{
		for (auto& objectList : m_SceneObject)
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
	
	template<class T>
	inline std::array<std::list<GameObject*>, 4> yUno_SceneManager::GetAllObjects()
	{
		return std::array<std::list<GameObject*>, 4>();
	}
}

using namespace yUno_SceneManagement;
