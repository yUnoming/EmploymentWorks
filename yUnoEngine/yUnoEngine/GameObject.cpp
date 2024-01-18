// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"

#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "Shader.h"
#include "BoxCollider.h"

#include "SceneBase.h"
#include "EditScene.h"

#include "yUno_GameObjectManager.h"
#include "yUno_SceneManager.h"
#include "yUno_ComponentManager.h"
#include "yUno_CollisionManager.h"
#include "SceneManager.h"

#include <algorithm>

using namespace PublicSystem;


void GameObject::CheckAddComponent(Component* com)
{
	// �����蔻��R���|�[�l���g��ǉ�����H
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
		yUno_SystemManager::yUno_CollisionManager::Push(colCom);	// �i�[����
}

void GameObject::CheckDeleteComponent(Component* com)
{
	// �����蔻��R���|�[�l���g��ǉ�����H
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
		yUno_SystemManager::yUno_CollisionManager::Erase(colCom);	// ���O����
}

GameObject::GameObject()
{
	// �I�u�W�F�N�g���̏�����
	ZeroMemory(m_name, sizeof(m_name));
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform> ();
	// Shader�R���|�[�l���g��ǉ�
	AddComponent<PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
}

GameObject::GameObject(SceneBase* nowScene)
{
	// �I�u�W�F�N�g���̏�����
	ZeroMemory(m_name, sizeof(m_name));
	// Transform�R���|�[�l���g��ǉ�
	transform = AddComponent <PublicSystem::Transform>();
	// Shader�R���|�[�l���g��ǉ�
	AddComponent<PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
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
		strcpy_s(m_name, newName);
	}
}

void GameObject::CopyName(const char* name)
{
	// �I�u�W�F�N�g����������
	ZeroMemory(m_name, sizeof(m_name));

	// �I�u�W�F�N�g����t����H
	if (name)
		strcpy_s(m_name, name);
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
	m_lateComponentList.clear();

	// �I�u�W�F�N�g�̏I������
	UnInit();
}

bool GameObject::UpdateBase()
{
	int index = 0;	// �v�f��

	// �e�R���|�[�l���g�̍X�V����
	for (auto com : m_componentList)
	{
// �f�o�b�O���̏���
#if _DEBUG
		// �f���v���C���H
		yUnoEngine::EditScene* editScene = (yUnoEngine::EditScene*)yUno_SceneManager::GetEditScene();
		if (editScene->IsDemoPlay())
			com->Update();	// �X�V����
		else if ((Text*)com)
			com->Update();	// �X�V����
		else if (editScene == m_myScene)
			com->Update();	// �X�V����
// �f�o�b�O���ȊO
#else
		com->Update();	// �X�V����
#endif
// �ʏ폈��		
		// �X�y�N�e�C�^�[�J�����ȊO�H
		if (strcmp(com->gameObject->GetName(), "SpectatorCamera") != 0)
		{
			// �I�u�W�F�N�g�����b�N����Ă��Ȃ��H
			if (!yUno_SystemManager::yUno_NetWorkManager::GetServer()->IsRockObject(GetName()))
				// �l���X�V����Ă����烁�b�Z�[�W�𑗂�
				yUno_SystemManager::yUno_ComponentManager::SendMessageBasedOnType(*std::next(m_lateComponentList.begin(), index), com);

			// ���݂̒l��ۑ�
			yUno_SystemManager::yUno_ComponentManager::SetVariableValue(*std::next(m_lateComponentList.begin(), index), com);
		}
		// �J�E���g�𑝂₷
		index++;
	}
// �f�o�b�O���̏���
#if _DEBUG
	// �f���v���C���H
	yUnoEngine::EditScene* editScene = (yUnoEngine::EditScene*)yUno_SceneManager::GetEditScene();
	if (editScene->IsDemoPlay())
		Update();	// �I�u�W�F�N�g�̍X�V����
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

void GameObject::DrawBase()
{
	// ���X�g���̃R���|�[�l���g�擾
	for (auto com : m_componentList)
		com->Draw();	// �`�揈��

	// �I�u�W�F�N�g�̕`�揈��
	Draw();
}
