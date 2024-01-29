#include "SystemNetWorkManager.h"
#include "SystemGameObjectManager.h"
#include "SystemCollisionManager.h"
#include "SystemSceneManager.h"

#include "SceneBase.h"
#include "EditScene.h"
#include "Camera.h"
#include "Message.h"


void Ctlan::PrivateSystem::SceneBase::Delete(GameObject* object)
{
	// �I�u�W�F�N�g�������폜
	Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::DeleteObjectNameData(object->GetName());
	if (object->GetComponent<BoxCollider>())
		Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(object->GetComponent<BoxCollider>());

	// ===== �I�u�W�F�N�g�폜�̃��b�Z�[�W�𑗂� ===== //
	// �C���X�^���X����
	MessageData messageData;
	// ������
	messageData.message.header.type = MessageType::ObjectDelete;	// ���b�Z�[�W���
	messageData.message.body.object.SetName(object->GetName());		// �I�u�W�F�N�g��
	// ���b�Z�[�W�𑗂�
	Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->SendMessageData(messageData);
}

Ctlan::PrivateSystem::SceneBase::SceneBase()
{
	ZeroMemory(m_sceneName, sizeof(m_sceneName));
}

void Ctlan::PrivateSystem::SceneBase::Init()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->InitBase();	// ����������
		}
	}
}

void Ctlan::PrivateSystem::SceneBase::Uninit()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->UninitBase();	// �I������
			delete object;			// �폜
		}
		//���X�g�̃N���A
		objectList.clear();
	}
}

void Ctlan::PrivateSystem::SceneBase::Update()
{
	bool isDestroy;
	std::list<GameObject*> destroyObjectList;

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			// �A�N�e�B�u��ԁH
			if (object->isActive)
			{
				isDestroy = object->UpdateBase();	// �X�V����(�߂�l�ō폜�t���O�擾)
				
				// �I�u�W�F�N�g���폜����H
				if (isDestroy)
					destroyObjectList.push_back(object);	// �폜�p���X�g�Ɋi�[
			}
		}
	}

	// �폜����I�u�W�F�N�g�����݂���H
	if (!destroyObjectList.empty())
	{
		// �I�u�W�F�N�g�����[�v
		for (GameObject* object : destroyObjectList)
		{
			DeleteSceneObject(object);	// �V�[������I�u�W�F�N�g���폜
		}
	}
}

void Ctlan::PrivateSystem::SceneBase::Draw()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
// �f�o�b�O���̏���
#if _DEBUG
			// �f���v���C���ł͂Ȃ��H
			if(!dynamic_cast<EngineScene::EditScene*>(SystemManager::SystemSceneManager::GetEditScene())->IsDemoPlay())
			{
				// �J�����R���|�[�l���g�������Ă���H
				if (object->GetComponent<Camera>())
					continue;	// ���̃I�u�W�F�N�g�ɑJ��
			}

#endif
// �ʏ�̏���
			// �A�N�e�B�u��ԁH
			if(object->isActive)
				object->DrawBase();	// �`�揈��
		}
	}
}
