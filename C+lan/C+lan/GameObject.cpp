// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SystemNetWorkManager.h"

#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "Shader.h"
#include "BoxCollider.h"

#include "SceneBase.h"
#include "EditScene.h"

#include "SystemGameObjectManager.h"
#include "SystemSceneManager.h"
#include "SystemComponentManager.h"
#include "SystemCollisionManager.h"
#include "SceneManager.h"

#include <algorithm>


void Ctlan::PrivateSystem::GameObject::CheckAddComponent(Component* com)
{
	// �����蔻��R���|�[�l���g��ǉ�����H
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
	{
		Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Push(colCom);	// �i�[����
	}
}

void Ctlan::PrivateSystem::GameObject::CheckDeleteComponent(Component* com)
{
	// �����蔻��R���|�[�l���g��ǉ�����H
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
	{
		Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(colCom);	// ���O����
	}
}

Ctlan::PrivateSystem::GameObject::GameObject()
{
	// �I�u�W�F�N�g���̏�����
	ZeroMemory(m_name, sizeof(m_name));
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <Ctlan::PublicSystem::Transform> ();
	// Shader�R���|�[�l���g��ǉ�
	AddComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
}

Ctlan::PrivateSystem::GameObject::GameObject(SceneBase* nowScene)
{
	// �I�u�W�F�N�g���̏�����
	ZeroMemory(m_name, sizeof(m_name));
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <Ctlan::PublicSystem::Transform>();
	// Shader�R���|�[�l���g��ǉ�
	AddComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
	// ���݃V�[����������
	m_myScene = nowScene;
}

void Ctlan::PrivateSystem::GameObject::SetName(const char* name)
{
	// �I�u�W�F�N�g����������
	ZeroMemory(m_name, sizeof(m_name));
	
	// �I�u�W�F�N�g����t����H
	if (name)
	{
		// �I�u�W�F�N�g��������Ă��Ȃ����m�F���A
		// ���ۂɕt����I�u�W�F�N�g�����擾����
		const char* newName = SystemManager::SystemGameObjectManager::CheckObjectName(name);
		strcpy_s(m_name, newName);
	}
}

void Ctlan::PrivateSystem::GameObject::CopyName(const char* name)
{
	// �I�u�W�F�N�g����������
	ZeroMemory(m_name, sizeof(m_name));

	// �I�u�W�F�N�g����t����H
	if (name)
		strcpy_s(m_name, name);
}

void Ctlan::PrivateSystem::GameObject::InitBase()
{
	int index = 0;	// �v�f��

	// �e�R���|�[�l���g�̏����l�ۑ�
	for (auto com : m_componentList)
	{
		// ���݂̒l��ۑ�
		SystemManager::SystemComponentManager::SetVariableValue(*std::next(m_lateComponentList.begin(), index), com);
		index++;
	}

	// �I�u�W�F�N�g�̏���������
	Init();
}

void Ctlan::PrivateSystem::GameObject::UninitBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_componentList)
	{
		com->Uninit();	// �I������
		delete com;		// �폜
	}

	// ���X�g���N���A
	m_componentList.clear();
	m_lateComponentList.clear();

	// �I�u�W�F�N�g�����폜
	SystemManager::SystemGameObjectManager::DeleteObjectNameData(m_name);
	// �I�u�W�F�N�g�̏I������
	Uninit();
}

bool Ctlan::PrivateSystem::GameObject::UpdateBase()
{
	int index = 0;	// �v�f��

	// �e�R���|�[�l���g�̍X�V����
	for (auto com : m_componentList)
	{
// �f�o�b�O���̏���
#if _DEBUG
		// �f���v���C���H
		Ctlan::EngineScene::EditScene* editScene = (EngineScene::EditScene*)SystemManager::SystemSceneManager::GetEditScene();
		if (editScene->IsDemoPlay())
		{
			com->Update();	// �X�V����
		}
		// �f���v���C���ł͂Ȃ�
		else
		{
			// �e�L�X�g�R���|�[�l���g�H
			if (dynamic_cast<Text*>(com) != nullptr)
				com->Update();	// �X�V����
			// �G�f�B�b�g�p�̃I�u�W�F�N�g�H
			else if (editScene == m_myScene)
				com->Update();	// �X�V����

			// �G�f�B�b�g�p�̃I�u�W�F�N�g�ł͂Ȃ��H
			if (editScene != m_myScene)
			{
				// �I�u�W�F�N�g�����b�N����Ă��Ȃ��H
				if (!SystemManager::SystemNetWorkManager::GetServer()->IsRockObject(GetName()))
					// �l���X�V����Ă����烁�b�Z�[�W�𑗂�
					SystemManager::SystemComponentManager::SendMessageBasedOnType(*std::next(m_lateComponentList.begin(), index), com);

				// ���݂̒l��ۑ�
				SystemManager::SystemComponentManager::SetVariableValue(*std::next(m_lateComponentList.begin(), index), com);
			}
			index++;		// �J�E���g�𑝂₷
		}
#else
		// �ʏ폈��		
		com->Update();	// �X�V����
#endif
	}
// �f�o�b�O���̏���
#if _DEBUG
	// �f���v���C���H
	EngineScene::EditScene* editScene = (EngineScene::EditScene*)SystemManager::SystemSceneManager::GetEditScene();
	if (editScene->IsDemoPlay())
		Update();	// �I�u�W�F�N�g�̍X�V����
	// �G�f�B�b�g�p�̃I�u�W�F�N�g�H
	else if (editScene == m_myScene)
		Update();	// �I�u�W�F�N�g�̍X�V����
// �f�o�b�O���ȊO
#else
	// �I�u�W�F�N�g�̍X�V����
	Update();
#endif
// �ʏ폈��
	// �I�u�W�F�N�g���폜����H
	if (isDestroy)
		return true;
	return false;
}

void Ctlan::PrivateSystem::GameObject::DrawBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_componentList)
		com->Draw();	// �`�揈��

	// �I�u�W�F�N�g�̕`�揈��
	Draw();
}
