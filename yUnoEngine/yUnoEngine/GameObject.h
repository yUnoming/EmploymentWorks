#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>
#include <SimpleMath.h>
#include <iostream>
#include "Component.h"

// ������������������������������ //
// �@�@		  �O���錾		 �@�@ //
// ������������������������������ //
namespace PublicSystem
{
	class Transform;	// PublicSystem::Transform���g�����߂̑O���錾
}

namespace yUno_SceneManagement
{
	class yUno_SceneManager;	// yUno_SceneManagement::yUno_SceneManager���g�����߂̑O���錾
}


// ������������������������������ //
// �@�@		 using�錾		 �@�@ //
// ������������������������������ //
using namespace PublicSystem;
using namespace yUno_SceneManagement;


class GameObject
{
	private:
		// ----- variables / �ϐ� ----- //
		// �R���|�[�l���g�̃��X�g
		std::list<Component*> m_Component_List;

		// �I�u�W�F�N�g��
		const char* m_Name = 0;

		// ���g������V�[���̏��
		yUno_SceneManager* m_MyScene = nullptr;


		// ----- functions / �֐� ----- //

	protected:
		// ----- variables / �ϐ� ----- //
		// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�\��
		// true: �ʏ퓮�� false: �@�\��~�E��\��
		bool m_Active = true;

	public:
		// ----- variables / �ϐ� ----- //
		// ��{�̃I�u�W�F�N�g���
		Transform* transform = nullptr;

		// ----- functions / �֐� ----- //
		GameObject();
		GameObject(yUno_SceneManager* _nowScene);
		virtual ~GameObject() {};

		// �I�u�W�F�N�g�P�̂Ɋւ�鏈��
		virtual void Init() {};			// ������
		virtual void UnInit() {};		// �I��
		virtual void Update() {};		// �X�V
		virtual void Draw() {};			// �`��
		
		// �����蔻�肪���������ꍇ
		virtual void HitCollision()
		{
			for (auto com : m_Component_List)
			{
				com->HitCollision();
			}
		};

		// �I�u�W�F�N�g�S�̂Ɋւ�鏈��
		void InitBase();
		void UnInitBase();
		void UpdateBase();
		void DrawBase(DirectX::SimpleMath::Matrix _parentMatrix);

		//**  �R���|�[�l���g����  **//
		/// <summary>
		// �@���e�F�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾����
		// �@�����F�Ȃ�
		// �߂�l�F�R���|�[�l���g�������Ă���ꍇ ===>>   �����Ă���R���|�[�l���g��Ԃ�
		//		   �R���|�[�l���g�������Ă��Ȃ��ꍇ ===>> nullptr��Ԃ�
		/// </summary>
		template<class T>
		T* GetComponent()
		{
			for (auto com : m_Component_List)
			{
				T* Component = dynamic_cast<T*>(com);
				if (Component != nullptr)
					return Component;
			}
			return nullptr;
		}

		/// <summary>
		// �@���e�F�I�u�W�F�N�g�ɐV���ɃR���|�[�l���g��ǉ�����
		// �@�����F�Ȃ�
		// �߂�l�F�ǉ������R���|�[�l���g
		/// </summary>
		template<class T>
		T* AddComponent()
		{
			T* com = new T();	

			// �R���|�[�l���g�Ɏ��g���ǉ������I�u�W�F�N�g����
			com->Myself = this;

			if(transform != nullptr)			// Transform�R���|�[�l���g�����g�ɒǉ�����Ă���H
				com->transform = transform;		// �ǉ�����R���|�[�l���g��Transform������

			m_Component_List.push_back(com);	// �R���|�[�l���g���X�g�ɒǉ�
			//Set_FitComponentList<T>(com);		// �K�������X�g�ɓ����֐������s

			((Component*)com)->Init();
			return com;
		}

		/// <summary>
		// �@���e�F�I�u�W�F�N�g�������Ă���R���|�[�l���g���폜����
		// �@�����F�Ȃ�
		// �߂�l�Fnullptr
		/// </summary>
		template<class T>
		void DeleteComponent()
		{
			for (auto com : m_Component_List)
			{
				T* Component = dynamic_cast<T*>(com);
				if (Component != nullptr)
				{
					Component->UnInit();
					delete Component;
				}
			}
		}
};