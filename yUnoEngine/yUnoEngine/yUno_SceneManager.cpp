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

	// �r���[�ϊ����쐬
	DirectX::SimpleMath::Matrix m_ViewMatrix;

	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
	//	m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//�v���W�F�N�V�����s��̐���
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // ����p

	float aspectRatio = static_cast<float>(960) / static_cast<float>(540);	// �A�X�y�N�g��	
	float nearPlane = 1.0f;       // �j�A�N���b�v
	float farPlane = 1000.0f;      // �t�@�[�N���b�v

	//�v���W�F�N�V�����s��̐���
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// ����n�ɂ����@20230511 by suzuki.tomoki

	// DIRECTXTK�̃��\�b�h�͉E��n�@20230511 by suzuki.tomoki
	// �E��n�ɂ���ƂR�p�`���_�������v���ɂȂ�̂ŕ`�悳��Ȃ��Ȃ�̂Œ���
	// ���̃R�[�h�͊m�F�e�X�g�̂��߂Ɏc��
//	projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);

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
