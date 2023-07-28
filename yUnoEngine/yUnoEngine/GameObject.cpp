// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include <d3d11.h>


void PublicSystem::GameObject::InitBase()
{
	// �I�u�W�F�N�g�̏���������
	Init();
}

void PublicSystem::GameObject::UnInitBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_ComponentList)
	{
		com->UnInit();	// �I������
		delete com;		// �폜
	}

	// ���X�g���N���A
	m_ComponentList.clear();

	// �I�u�W�F�N�g�̏I������
	UnInit();
}

void PublicSystem::GameObject::UpdateBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_ComponentList)
		com->Update();	// �X�V����

	// �I�u�W�F�N�g�̍X�V����
	Update();
}

void PublicSystem::GameObject::DrawBase(DirectX::SimpleMath::Matrix _parentMatrix)
{
	// �}�g���b�N�X�ݒ�
	DirectX::SimpleMath::Matrix world, trans, rot, scl;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	scl = DirectX::SimpleMath::Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	world = trans * rot * scl * _parentMatrix;

	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_ComponentList)
		com->Draw();	// �`�揈��

	// �I�u�W�F�N�g�̕`�揈��
	Draw();
}

// �@���e�F�I�u�W�F�N�g�������Ă���R���|�[�l���g���擾����
// �@�����F�Ȃ�
// �߂�l�F�R���|�[�l���g�������Ă���ꍇ ===>>   �����Ă���R���|�[�l���g��S�ĕԂ�
//		   �R���|�[�l���g�������Ă��Ȃ��ꍇ ===>> nullptr��Ԃ�
template<class T>
T* PublicSystem::GameObject::GetComponent()
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
T* PublicSystem::GameObject::AddComponent()
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
T* PublicSystem::GameObject::DeleteComponent()
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
