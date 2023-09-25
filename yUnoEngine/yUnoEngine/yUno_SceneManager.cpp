// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_SceneManager.h"
#include "SampleScene.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include <SimpleMath.h>

std::array<std::list<GameObject*>, 4> yUno_SceneManager::m_SceneObject;


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
	// Box�^�̓����蔻��p���X�g���쐬
	std::list<BoxCollider*> BoxCollider_List;

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->UpdateBase();	// �X�V����
			
			// "BoxCollider"�R���|�[�l���g���擾
			BoxCollider *boxcol = object->GetComponent<BoxCollider>();
			// �擾�o�����H
			if (boxcol != nullptr)
				BoxCollider_List.push_back(boxcol);	// ���X�g�Ɋi�[���Ă���
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//�����_��
	}

	// ���葤�̓����蔻��p���X�g���쐬
	std::list<BoxCollider*> Other_BoxCollider_List = BoxCollider_List;
	Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());

	// ===== "BoxCollider"���m�̓����蔻�� ===== //
	for (auto my_BoxCol : BoxCollider_List)
	{
		// �����蔻���S�ʂ�s�����H
		if (Other_BoxCollider_List.empty())
			break;	// ����I��

		for (auto other_BoxCol : Other_BoxCollider_List)
		{
			my_BoxCol->CalcCollision(other_BoxCol);	// �v�Z����
		}

		// �����蔻��̑���p���X�g�̂O�Ԗځi�n�߂Ɋi�[����Ă�����j���폜����
		// �������蔻����d�����Ĕ��肷�邱�Ƃ�j�~���邽��
		Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());
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
