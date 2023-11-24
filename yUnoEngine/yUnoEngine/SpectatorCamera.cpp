// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "SpectatorCamera.h"
#include "Transform.h"
#include "Camera.h"

#include "KeyInput.h"
#include "InputPartsName.h"
#include "MouseInput.h"
#include "ScreenInput.h"
#include "Material.h"


// ������������������������������ //
// �@�@		  using�錾		 �@�@ //
// ������������������������������ //
using namespace PublicSystem;


void SpectatorCamera::Init()
{
	// �R���|�[�l���g�ǉ�
	AddComponent<Camera>();
}

void SpectatorCamera::Update()
{
	// ===== ���g�̑��� ===== //
	if (KeyInput::GetKeyDown(UpArrow))
		transform->Position.y += 0.01f;
	if (KeyInput::GetKeyDown(LeftArrow))
		transform->Position.x -= 0.01f;
	if (KeyInput::GetKeyDown(DownArrow))
		transform->Position.y -= 0.01f;
	if (KeyInput::GetKeyDown(RightArrow))
		transform->Position.x += 0.01f;

	// ===== ����p�̏k���E�g�� ===== //
	//if (MouseInput::GetWheelRotation_Forward())
	//{
	//	GetComponent<Camera>()->FieldOfView -= 0.5f;
	//}
	//else if (MouseInput::GetWheelRotation_Backward())
	//{
	//	GetComponent<Camera>()->FieldOfView += 0.5f;
	//}

	// ===== �N���b�N�����I�u�W�F�N�g���擾 ===== //
	// ���N���b�N���ꂽ�H
	if (MouseInput::GetMouseDownTrigger(LeftButton))
	{
		// �N���b�N�����I�u�W�F�N�g���ꎞ�I�ɑ������ϐ�
		GameObject* tmpClickedObject;

		// �N���b�N�����ʒu�ɃI�u�W�F�N�g������ꍇ�A���̃I�u�W�F�N�g���擾
		// �擾���ꂽ��ԂŃI�u�W�F�N�g���Ȃ��ꏊ���N���b�N���ꂽ��A�擾����������
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		
		// �N���b�N���ꂽ�I�u�W�F�N�g�����b�N����Ă����珈�����I��
		if (tmpClickedObject && yUno_SystemManager::yUno_NetWorkManager::GetServer()->IsRockObject(tmpClickedObject->GetName()))
			return;

		// ----- ���݂̃N���b�N��Ԃɂ���ď����𕪊� ----- //
		// �ʂ̃I�u�W�F�N�g���N���b�N���ꂽ�H
		if (tmpClickedObject && m_clickedObject && tmpClickedObject != m_clickedObject)
		{
			// �N���b�N����Ă����I�u�W�F�N�g�̃}�e���A����ύX
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			
			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_clickedObject = tmpClickedObject;
			// �N���b�N���ꂽ�I�u�W�F�N�g�̃}�e���A����ύX
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 0.0f, 0.0f, 1.0f));

			// ���郁�b�Z�[�W��������z��
			char sendMessage[256];
			ZeroMemory(sendMessage, sizeof(sendMessage));

			// ���肽�����𕶎���ɒu��
			sprintf_s(sendMessage, "%d %s",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject,	// ���M���郁�b�Z�[�W�̃^�C�v
				m_clickedObject->GetName());											// �I�u�W�F�N�g��
				// ���b�Z�[�W�𑗂鏈�������s
				yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// �I�u�W�F�N�g���N���b�N���ꂽ�H
		else if (tmpClickedObject)
		{
			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_clickedObject = tmpClickedObject;
			// �N���b�N���ꂽ�I�u�W�F�N�g�̃}�e���A����ύX
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 0.0f, 0.0f, 1.0f));

			// ���郁�b�Z�[�W��������z��
			char sendMessage[256];
			ZeroMemory(sendMessage, sizeof(sendMessage));

			// ���肽�����𕶎���ɒu��
			sprintf_s(sendMessage, "%d %s",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject,	// ���M���郁�b�Z�[�W�̃^�C�v
				m_clickedObject->GetName());											// �I�u�W�F�N�g��
			// ���b�Z�[�W�𑗂鏈�������s
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// �I�u�W�F�N�g���������ꂽ�H
		else if (!tmpClickedObject && m_clickedObject)
		{
			// �N���b�N����Ă����I�u�W�F�N�g�̃}�e���A����ύX
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			// �N���b�N�I�u�W�F�N�g������
			m_clickedObject = nullptr;

			// ���郁�b�Z�[�W��������z��
			char sendMessage[256];
			ZeroMemory(sendMessage, sizeof(sendMessage));

			// ���肽�����𕶎���ɒu��
			sprintf_s(sendMessage, "%d %s",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject,	// ���M���郁�b�Z�[�W�̃^�C�v
				nullptr);																// �I�u�W�F�N�g��
			// ���b�Z�[�W�𑗂鏈�������s
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
	}

	// ===== �N���b�N�����I�u�W�F�N�g�̑��� ===== //
	// �I�u�W�F�N�g���擾���Ă���H
	if (m_clickedObject)
	{
		if (KeyInput::GetKeyDown(W))
			m_clickedObject->transform->Position.z += 0.01f;
		if (KeyInput::GetKeyDown(A))
			m_clickedObject->transform->Position.x -= 0.01f;
		if (KeyInput::GetKeyDown(S))
			m_clickedObject->transform->Position.z -= 0.01f;
		if (KeyInput::GetKeyDown(D))
			m_clickedObject->transform->Position.x += 0.01f;
	}	
}
