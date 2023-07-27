// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_SceneManager.h"
#include "GameObject.h"
#include <SimpleMath.h>


void yUno_SceneManager::InitBase()
{
	// ���݃V�[���̏���������
	Init();
}

void yUno_SceneManager::UnInitBase()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_SceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (PublicSystem::GameObject* object : objectList)
		{
			object->UnInit();	// �I������
			delete object;		// �폜
		}
		objectList.clear();		//���X�g�̃N���A
	}
	// ���݃V�[���̏I������
	UnInit();
}

void yUno_SceneManager::UpdateBase()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_SceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (PublicSystem::GameObject* object : objectList)
		{
			object->Update();	// �X�V����
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//�����_��
	}

	// ���݃V�[���̍X�V����
	Update();
}

void yUno_SceneManager::DrawBase()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_SceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (PublicSystem::GameObject* object : objectList)
		{
			object->Draw();	// �`�揈��
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//�����_��
	}

	// ���݃V�[���̕`�揈��
	Draw();
}
