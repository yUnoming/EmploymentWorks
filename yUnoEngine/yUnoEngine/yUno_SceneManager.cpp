// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_SceneManager.h"
#include "SampleScene.h"
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
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->UnInitBase();	// �I������
			delete object;			// �폜
		}
		objectList.clear();	//���X�g�̃N���A
	}
	// ���݃V�[���̏I������
	m_LoadedScene->UnInit();
}

void yUno_SceneManager::UpdateBase()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->UpdateBase();	// �X�V����
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//�����_��
	}

	// ���݃V�[���̍X�V����
	m_LoadedScene->Update();
}


#include "renderer.h"
void yUno_SceneManager::DrawBase()
{
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->DrawBase(matrix);	// �`�揈��
		}
	}

	// ���݃V�[���̕`�揈��
	m_LoadedScene->Draw();
}
