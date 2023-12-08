// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "yUno_GameObjectManager.h"
#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "Shader.h"
#include "BoxCollider.h"
#include "yUno_SceneManager.h"
#include "yUno_ComponentManager.h"

#include <algorithm>

using namespace PublicSystem;

GameObject::GameObject()
{
	// �I�u�W�F�N�g���̏�����
	ZeroMemory(m_name, sizeof(m_name));
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform> ();
	// Shader�R���|�[�l���g��ǉ�
	AddComponent<PublicSystem::Shader>()->Load("Assets\\Shaders\\unlitTextureVS.cso", "Assets\\Shaders\\unlitTexturePS.cso");
}

GameObject::GameObject(yUno_SceneManager* nowScene)
{
	// �I�u�W�F�N�g���̏�����
	ZeroMemory(m_name, sizeof(m_name));
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform>();
	// Shader�R���|�[�l���g��ǉ�
	AddComponent<PublicSystem::Shader>()->Load("Assets\\Shaders\\unlitTextureVS.cso", "Assets\\Shaders\\unlitTexturePS.cso");
	// ���݃V�[����������
	m_myScene = nowScene;
}

void GameObject::SetName(const char* name)
{
	// �I�u�W�F�N�g����������
	ZeroMemory(m_name, sizeof(m_name));
	
	// �I�u�W�F�N�g����t����H
	if (name)
	{
		// �I�u�W�F�N�g��������Ă��Ȃ����m�F���A
		// ���ۂɕt����I�u�W�F�N�g�����擾����
		const char* newName = yUno_SystemManager::yUno_GameObjectManager::CheckObjectName(name);
		memcpy_s(m_name, sizeof(m_name), newName, strlen(newName));
	}
}

void GameObject::CopyName(const char* name)
{
	// �I�u�W�F�N�g����������
	ZeroMemory(m_name, sizeof(m_name));

	// �I�u�W�F�N�g����t����H
	if (name)
		memcpy_s(m_name, sizeof(m_name), name, strlen(name));
}

void GameObject::InitBase()
{
	// �I�u�W�F�N�g�̏���������
	Init();
}

void GameObject::UnInitBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_componentList)
	{
		com->UnInit();	// �I������
		delete com;		// �폜
	}

	// ���X�g���N���A
	m_componentList.clear();
	m_lateCompoenntList.clear();

	// �I�u�W�F�N�g�̏I������
	UnInit();
}

void GameObject::UpdateBase()
{
	int index = 0;	// �v�f��

	// �e�R���|�[�l���g�̍X�V����
	for (auto com : m_componentList)
	{
		com->Update();
		
		// �I�u�W�F�N�g�����b�N����Ă��Ȃ��H
		if (!yUno_SystemManager::yUno_NetWorkManager::GetServer()->IsRockObject(GetName()))
			// �l���X�V����Ă����烁�b�Z�[�W�𑗂�
			yUno_SystemManager::yUno_ComponentManager::SendMessageBasedOnType(*std::next(m_lateCompoenntList.begin(), index), com);

		// ���݂̒l��ۑ�
		yUno_SystemManager::yUno_ComponentManager::SetVariableValue(*std::next(m_lateCompoenntList.begin(), index), com);
		// �J�E���g�𑝂₷
		index++;
	}
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
	for (auto com : m_componentList)
		com->Draw();	// �`�揈��

	// �I�u�W�F�N�g�̕`�揈��
	Draw();
}
