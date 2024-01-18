#pragma once
/**
* @file		yUno_MainManager.h
* @brief	yUno_MainManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>
#include <array>
#include <vector>
#include "BoxCollider.h"


/// <summary>
///	�V�[���̊�b�ƂȂ�N���X	</summary>
class SceneBase
{
	private:
		// ----- functions / �֐� ----- // 
		/// <summary>
		///	�I�u�W�F�N�g�폜����	</summary>
		/// <param name="object">
		/// �폜����I�u�W�F�N�g	</param>
		void Delete(GameObject* object);

	protected:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		///	�V�[����	</summary>
		char m_sceneName[30];

		/// <summary>
		/// �V�[�����̃I�u�W�F�N�g	</summary>
		std::array<std::list<GameObject*>, 4> m_sceneObjectList;

		// Box�^�̓����蔻��p���X�g���쐬
		std::vector<BoxCollider*> m_boxColliderList;

	public:
		// ----- functions / �֐� ----- //
		/// <summary>
		///	�R���X�g���N�^	</summary>
		SceneBase();
		SceneBase(const char* sceneName) { strcpy_s(m_sceneName, sceneName); };

		/// <summary>
		///	�f�X�g���N�^	</summary>
		virtual ~SceneBase() {};

		//**  �V�[���P�̂Ɋւ�鏈��  **//	
		/// <summary>
		///	������	</summary>
		virtual void Init() {};
		/// <summary>
		///	�I��	</summary>
		virtual void UnInit();
		/// <summary>
		///	�X�V	</summary>
		virtual void Update();
		/// <summary>
		///	�`��	</summary>
		virtual void Draw();

		char* GetSceneName() { return m_sceneName; };

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
			T* obj = new T();							// �I�u�W�F�N�g�𐶐�
			obj->CopyName(name);						// �I�u�W�F�N�g����ݒ�
			m_sceneObjectList[layer].push_back(obj);	// �w�肳�ꂽ�v�f�ʒu�ɕۑ�
			obj->Init();								// �I�u�W�F�N�g�̏�����

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
			T* obj = new T(this);						// �I�u�W�F�N�g�𐶐�
			obj->SetName(name);							// �I�u�W�F�N�g����ݒ�
			m_sceneObjectList[layer].push_back(obj);	// �w�肳�ꂽ�v�f�ʒu�ɕۑ�
			obj->Init();								// �I�u�W�F�N�g�̏�����

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
			for (auto& objectList : m_sceneObjectList)
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
			for (auto& objectList : m_sceneObjectList)
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
		///	�V�[������I�u�W�F�N�g���폜	</summary>
		/// <param name="name">
		/// �폜����I�u�W�F�N�g�̖���	</param>
		void DeleteSceneObject(const char* name)
		{
			// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
			for (auto& objectList : m_sceneObjectList)
			{
				// ���X�g���̃I�u�W�F�N�g�擾
				for (GameObject* object : objectList)
				{
					// ���̂���v�����H
					if (strcmp(object->GetName(), name) == 0)
					{
						// �폜����
						Delete(object);
						// �I�u�W�F�N�g���X�g���珜�O
						objectList.erase(std::find(objectList.begin(), objectList.end(), object));
						// �I�u�W�F�N�g���폜
						delete object;
						return;
					}
				}
			}
		}
		/// <summary>
		///	�V�[������I�u�W�F�N�g���폜	</summary>
		/// <param name="name">
		/// �폜����I�u�W�F�N�g���	</param>
		void DeleteSceneObject(GameObject* deleteObj)
		{
			// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
			for (auto& objectList : m_sceneObjectList)
			{
				// ���X�g���̃I�u�W�F�N�g�擾
				for (GameObject* object : objectList)
				{
					// �I�u�W�F�N�g����v�����H
					if (object == deleteObj)
					{
						// �폜����
						Delete(object);
						// �I�u�W�F�N�g���X�g���珜�O
						objectList.erase(std::find(objectList.begin(), objectList.end(), object));
						return;
					}
				}
			}
		}


		/// <summary>
		/// ���݃V�[���ɑ��݂���I�u�W�F�N�g��S�擾	</summary>
		/// <returns>
		///	�S�I�u�W�F�N�g�����������X�g	</returns>
		std::array<std::list<GameObject*>, 4> GetAllSceneObjects()
		{
			return m_sceneObjectList;
		}
};

