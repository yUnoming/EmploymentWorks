// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "yUno_SceneManager.h"
#include <algorithm>

using namespace PublicSystem;

GameObject::GameObject()
{
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform> ();
}

GameObject::GameObject(yUno_SceneManager* _nowScene)
{
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform>();
	// ���݃V�[����������
	m_MyScene = _nowScene;
}

void GameObject::InitBase()
{
	// �I�u�W�F�N�g�̏���������
	Init();
}

void GameObject::UnInitBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_Component_List)
	{
		com->UnInit();	// �I������
		delete com;		// �폜
	}

	// ���X�g���N���A
	m_Component_List.clear();

	// �I�u�W�F�N�g�̏I������
	UnInit();
}

void GameObject::UpdateBase()
{
	// �e�R���|�[�l���g�̍X�V����
	for (auto com : m_Component_List)
		com->Update();

	// �I�u�W�F�N�g�̍X�V����
	Update();
}

void GameObject::DrawBase(DirectX::SimpleMath::Matrix _parentMatrix)
{
	// �}�g���b�N�X�ݒ�
	DirectX::SimpleMath::Matrix world, trans, rot, scl;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(transform->Position.x, transform->Position.y, transform->Position.z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(transform->Rotation.y, transform->Rotation.x, transform->Rotation.z);
	scl = DirectX::SimpleMath::Matrix::CreateScale(transform->Scale.x, transform->Scale.y, transform->Scale.z);
	world = rot * trans * scl * _parentMatrix;

	Renderer::SetWorldMatrix(&world);

	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_Component_List)
		com->Draw();	// �`�揈��

	// �I�u�W�F�N�g�̕`�揈��
	Draw();
}
