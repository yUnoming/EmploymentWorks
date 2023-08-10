// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "renderer.h"

using namespace PublicSystem;

void GameObject::InitBase()
{
	// �I�u�W�F�N�g�̏���������
	Init();
}

void GameObject::UnInitBase()
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

void GameObject::UpdateBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_ComponentList)
		com->Update();	// �X�V����

	// �I�u�W�F�N�g�̍X�V����
	Update();
}

void GameObject::DrawBase(DirectX::SimpleMath::Matrix _parentMatrix)
{
	// �}�g���b�N�X�ݒ�
	DirectX::SimpleMath::Matrix world, trans, rot, scl;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	scl = DirectX::SimpleMath::Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	world = rot * trans * scl * _parentMatrix;

	Renderer::SetWorldMatrix(&world);

	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_ComponentList)
		com->Draw();	// �`�揈��

	// �I�u�W�F�N�g�̕`�揈��
	Draw();
}
