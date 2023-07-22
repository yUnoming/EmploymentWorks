#include "GameObject.h"

// �@���e�FGameObject�N���X�̃f�X�g���N�^
// �@�����F�Ȃ�
// �߂�l�F�Ȃ�
GameObject::~GameObject()
{
	// �R���|�[�l���g�̐��������[�v
	for (auto com : m_ComponentList)
		delete com;
}

// �@���e�F�I�u�W�F�N�g�������Ă���e��R���|�[�l���g���X�V���������s����
// �@�����F�Ȃ�
// �߂�l�F�Ȃ�
void GameObject::Update()
{
	for (auto com : m_ComponentList)
		com->Update();
}

// �@���e�F�I�u�W�F�N�g�������Ă���e��R���|�[�l���g�̕`�揈�������s����
// �@�����F�Ȃ�
// �߂�l�F�Ȃ�
void GameObject::Draw()
{
	for (auto com : m_ComponentList)
		com->Draw();
}

// �@���e�F�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾����
// �@�����F�Ȃ�
// �߂�l�F�R���|�[�l���g�������Ă���ꍇ ===>>   �����Ă���R���|�[�l���g��S�ĕԂ�
//		   �R���|�[�l���g�������Ă��Ȃ��ꍇ ===>> nullptr��Ԃ�
template<class T>
T* GameObject::GetComponent()
{
	for (auto com : m_ComponentList)
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
T* GameObject::AddComponent()
{
	T* Component = new T();
	m_ComponentList.push_back(Component);
	Component->Init();
	return Component;
}

// �@���e�F�I�u�W�F�N�g�������Ă���R���|�[�l���g���폜����
// �@�����F�Ȃ�
// �߂�l�Fnullptr
template<class T>
T* GameObject::DeleteComponent()
{
	for (auto com : m_ComponentList)
	{
		T* Component = dynamic_cast<T*>(com);
		if (Component != nullptr)
		{
			Component->UnInit();
			delete Component;
			return nullptr;
		}
	}
	return nullptr;
}
