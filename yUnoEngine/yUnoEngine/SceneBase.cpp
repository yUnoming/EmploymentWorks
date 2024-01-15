#include "yUno_NetWorkManager.h"
#include "yUno_GameObjectManager.h"
#include "yUno_CollisionManager.h"

#include "SceneBase.h"
#include "Camera.h"
#include "Message.h"


void SceneBase::Delete(GameObject* object)
{
	// �I�u�W�F�N�g�������폜
	yUno_SystemManager::yUno_GameObjectManager::DeleteObjectNameData(object->GetName());
	if (object->GetComponent<BoxCollider>())
		yUno_SystemManager::yUno_CollisionManager::Erase(object->GetComponent<BoxCollider>());

	// ===== �I�u�W�F�N�g�폜�̃��b�Z�[�W�𑗂� ===== //
	// �C���X�^���X����
	MessageData messageData;
	// ������
	messageData.message.header.type = MessageType::ObjectDelete;	// ���b�Z�[�W���
	messageData.message.body.object.SetName(object->GetName());		// �I�u�W�F�N�g��
	// ���b�Z�[�W�𑗂�
	yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendMessageData(messageData);
}

SceneBase::SceneBase()
{
	ZeroMemory(m_sceneName, sizeof(m_sceneName));
}

void SceneBase::UnInit()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->UnInitBase();	// �I������
			delete object;			// �폜
		}
		//���X�g�̃N���A
		objectList.clear();
	}
}

void SceneBase::Update()
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

void SceneBase::Draw()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
// �f�o�b�O���̏���
#if _DEBUG
			// �J�����R���|�[�l���g�������Ă���H
			if (object->GetComponent<Camera>())
				continue;	// ���̃I�u�W�F�N�g�ɑJ��
#endif
// �ʏ�̏���
			// �A�N�e�B�u��ԁH
			if(object->isActive)
				object->DrawBase();	// �`�揈��
		}
	}

}
