#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>
#include <SimpleMath.h>
#include "Component.h"


// ������������������������������ //
// �@�@		  �O���錾		 �@�@ //
// ������������������������������ //
namespace PublicSystem
{
	class Transform;	// PublicSystem::Transform���g�����߂ɑO���錾
}


// ������������������������������ //
// �@�@		 using�錾		 �@�@ //
// ������������������������������ //
using namespace PublicSystem;


class GameObject
{
	private:
		// ----- variables / �ϐ� ----- //
		// �R���|�[�l���g�̃��X�g
		std::list<Component*> m_Component_List;

		// �I�u�W�F�N�g��
		const char* m_Name = 0;

	protected:
		// ----- variables / �ϐ� ----- //
		// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�\��
		// true: �ʏ퓮�� false: �@�\��~�E��\��
		bool m_Active = true;

				// ��{�̃I�u�W�F�N�g���
		Transform* transform = nullptr;

	public:
		// ----- functions / �֐� ----- //
		GameObject();
		virtual ~GameObject() {};

		// �I�u�W�F�N�g�P�̂Ɋւ�鏈��
		virtual void Init() {};		// ������
		virtual void UnInit() {};	// �I��
		virtual void Update() {};	// �X�V
		virtual void Draw() {};		// �`��

		// �I�u�W�F�N�g�S�̂Ɋւ�鏈��
		void InitBase();
		void UnInitBase();
		void UpdateBase();
		void DrawBase(DirectX::SimpleMath::Matrix _parentMatrix);

		//**  �R���|�[�l���g����  **//

		// �@���e�F�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾����
		// �@�����F�Ȃ�
		// �߂�l�F�R���|�[�l���g�������Ă���ꍇ ===>>   �����Ă���R���|�[�l���g��S�ĕԂ�
		//		   �R���|�[�l���g�������Ă��Ȃ��ꍇ ===>> nullptr��Ԃ�
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

		// �@���e�F�I�u�W�F�N�g�ɐV���ɃR���|�[�l���g��ǉ�����
		// �@�����F�Ȃ�
		// �߂�l�F�ǉ������R���|�[�l���g
		template<class T>
		T* AddComponent()
		{
			T* com = new T();
			com->Myself = this;
			if(transform != nullptr)
				com->transform = transform;
			m_Component_List.push_back(com);
			((Component*)com)->Init();
			return com;
		}

		// �@���e�F�I�u�W�F�N�g�������Ă���R���|�[�l���g���폜����
		// �@�����F�Ȃ�
		// �߂�l�Fnullptr
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