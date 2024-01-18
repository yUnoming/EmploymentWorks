#pragma once
/**
* @file		GameObject.h
* @brief	GameObject�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>
#include <iostream>
#include "Component.h"


// ������������������������������ //
// �@�@		  �O���錾		 �@�@ //
// ������������������������������ //
class SceneBase;	// SceneBase���g�����߂̑O���錾

/// <summary>
/// ���[�U�[���g����V�X�e�� </summary>
namespace PublicSystem
{
	class Transform;	// PublicSystem::Transform���g�����߂̑O���錾
}


// ������������������������������ //
// �@�@		 using�錾		 �@�@ //
// ������������������������������ //
using namespace PublicSystem;

/// <summary>
/// �I�u�W�F�N�g�Ɏ����������v�f���܂Ƃ߂��N���X	</summary>
class GameObject
{
	private:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		/// �ێ����Ă���R���|�[�l���g���i�[���郊�X�g		</summary>
		std::list<Component*> m_componentList;
		/// <summary>
		/// ���݂̃R���|�[�l���g���Ɣ�r����ׂ̃��X�g	</summary>
		std::list<Component*> m_lateComponentList;

		/// <summary>
		/// �I�u�W�F�N�g��	</summary>
		char m_name[30];

		/// <summary>
		/// ���g������V�[���̏��		</summary>
		SceneBase* m_myScene = nullptr;

		/// <summary>
		///	�폜���邩�ǂ���	</summary>
		bool isDestroy;

		// ----- functions / �֐� ----- //
		/// <summary>
		/// �R���|�[�l���g�ǉ����̊m�F����	</summary>
		void CheckAddComponent(Component* com);
		/// <summary>
		///	�R���|�[�l���g�폜���̊m�F����	</summary>
		void CheckDeleteComponent(Component* com);

	public:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		/// �g�����X�t�H�[��	</summary>
		Transform* transform = nullptr;

		/// <summary>
		/// �I�u�W�F�N�g�̃A�N�e�B�u���
		/// �itrue: �A�N�e�B�u false: ��A�N�e�B�u�j</summary>
		bool isActive = true;

		// ----- functions / �֐� ----- //
		/// <summary>
		/// �R���X�g���N�^		</summary>
		GameObject();
		/// <summary>
		///	�����t���R���X�g���N�^	</summary>
		/// <param name="nowScene">
		///	���݂̃V�[��	</param>
		GameObject(SceneBase* nowScene);

		/// <summary>
		/// �f�X�g���N�^	</summary>
		virtual ~GameObject() {};

		/// <summary>
		///	�I�u�W�F�N�g���擾	</summary>
		/// <returns>
		///	�I�u�W�F�N�g��	</returns>
		const char* GetName() { return m_name; };
		/// <summary>
		///	�I�u�W�F�N�g����ݒ�	</summary>
		/// <param name="name">
		/// �ݒ肷��I�u�W�F�N�g��	</param>
		void SetName(const char* name);
		/// <summary>
		///	�I�u�W�F�N�g�����R�s�[	</summary>
		/// <param name="name">
		/// �R�s�[����I�u�W�F�N�g��	</param>
		void CopyName(const char* name);

		/// <summary>
		///	���g���폜����	</summary>
		void Destroy() { isDestroy = true; };

		// �I�u�W�F�N�g�P�̂Ɋւ�鏈��
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
		/// <summary>
		/// �����蔻�莞	</summary>
		virtual void HitCollision(GameObject* other)
		{
			// ���X�g���̃R���|�[�l���g������擾
			for (auto com : m_componentList)
			{
				com->HitCollision(other);
			}
		};

		// �I�u�W�F�N�g�S�̂Ɋւ�鏈��
		/// <summary>
		/// �x�[�X�̏���������	</summary>
		void InitBase();
		/// <summary>
		/// �x�[�X�̏I������	</summary>
		void UnInitBase();
		/// <summary>
		/// �x�[�X�̍X�V����	</summary>
		/// <returns>
		/// �폜���邩�ǂ���(true�Ȃ�I�u�W�F�N�g�폜) </returns>
		bool UpdateBase();
		/// <summary>
		/// �x�[�X�̕`�揈��	</summary>
		/// <param name="parentMatrix">
		///	�e�̍��W�s��i�e�����Ȃ��ꍇ�͐��K�����ꂽ���W�s��j	</param>
		void DrawBase();

		//**  �R���|�[�l���g����  **//
		/// <summary>
		/// �R���|�[�l���g���擾 </summary>
		/// <param name="GetComponent&lt;&gt;();">
		/// &lt;&gt;���Ɏ擾�������R���|�[�l���g���L�q		</param>
		/// <returns>
		/// �擾�����R���|�[�l���g </returns>
		template<class T>
		T* GetComponent()
		{
			// ���X�g���̃R���|�[�l���g������擾
			for (auto com : m_componentList)
			{
				T* component = dynamic_cast<T*>(com);
				
				// �擾�������R���|�[�l���g�ƍ��v�����H
				if (component != nullptr)
					return component;
			}
			return nullptr;
		}
		/// <summary>
		/// �ێ����Ă���R���|�[�l���g��S�擾	</summary>
		/// <returns>
		/// �S�R���|�[�l���g�����������X�g	</returns>
		std::list<Component*> GetComponentAll(){ return m_componentList; }
		/// <summary>
		/// �R���|�[�l���g��ǉ�
		/// </summary>
		/// <param name="AddComponent&lt;&gt;();">
		/// &lt;&gt;���ɒǉ��������R���|�[�l���g���L�q		</param>
		/// <returns>
		/// �ǉ������R���|�[�l���g		</returns>
		template<class T>
		T* AddComponent()
		{
			T* com = new T();	
			T* lateCom = new T();

			// �R���|�[�l���g���ǉ������I�u�W�F�N�g����
			com->gameObject = this;

			// Transform�R���|�[�l���g�����g�ɒǉ�����Ă���H
			if (transform != nullptr)
				com->transform = transform;			// �ǉ�����R���|�[�l���g��Transform������
			// Transform�R���|�[�l���g��ǉ�����
			else
				com->transform = (Transform*)com;	// �ǉ�����R���|�[�l���g����

			CheckAddComponent(com); // �m�F����

			((Component*)com)->Init();				// �R���|�[�l���g�̏���������
			m_componentList.push_back(com);			// �R���|�[�l���g���X�g�ɒǉ�
			m_lateComponentList.push_back(lateCom);	// ��r�p�ɃR���|�[�l���g���i�[
			
			return com;
		}
		/// <summary>
		/// �R���|�[�l���g���폜
		/// </summary>
		/// <param name="DeleteComponent&lt;&gt;();">
		/// &lt;&gt;���ɍ폜�������R���|�[�l���g���L�q		</param>
		template<class T>
		void DeleteComponent()
		{
			// ���X�g���̃R���|�[�l���g������擾
			for (auto com : m_componentList)
			{
				T* Component = dynamic_cast<T*>(com);
				
				// �擾�������R���|�[�l���g�ƍ��v�����H
				if (Component != nullptr)
				{
					CheckDeleteComponent();	// �m�F����

					Component->UnInit();	// �R���|�[�l���g�̏I������
					delete Component;
				}
			}
		}
};