// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SystemNetWorkManager.h"
#include "SpectatorCamera.h"
#include "Transform.h"
#include "Camera.h"

#include "Time.h"
#include "KeyInput.h"
#include "InputPartsName.h"
#include "MouseInput.h"
#include "ScreenInput.h"
#include "Material.h"


void Ctlan::EngineObject::SpectatorCamera::Init()
{
	// �R���|�[�l���g�ǉ�
	AddComponent<Camera>();
}

void Ctlan::EngineObject::SpectatorCamera::Update()
{
	// ===== �J�����̑��� ===== //
	// ----- �}�E�X�ŃJ�����ړ� ----- //
	// �z�C�[���{�^����������Ă���H
	if (MouseInput::GetMouseDown(ScrollWheelButton))
	{
		Vector2 moveAmount = MouseInput::GetCursorMoveAmount();
		Vector3 addVec = Vector3(moveAmount.x, moveAmount.y, 0.0f);
		transform->position += addVec.Rotate(transform->rotation) * 0.01f;
	}
	else
	{
		// ----- �L�[���͂ŃJ�����ړ� ----- //
	// ����L�[��������Ă���H
		if (KeyInput::GetKeyDown(UpArrow))
		{
			Vector3 addVec = Vector3(0.0f, 1.0f, 0.0f);
			transform->position += addVec.Rotate(transform->rotation) * 0.01f;
		}
		// �����L�[��������Ă���H
		if (KeyInput::GetKeyDown(LeftArrow))
		{
			Vector3 addVec = Vector3(-1.0f, 0.0f, 0.0f);
			transform->position += addVec.Rotate(transform->rotation) * 0.01f;
		}
		// �����L�[��������Ă���H
		if (KeyInput::GetKeyDown(DownArrow))
		{
			Vector3 addVec = Vector3(0.0f, -1.0f, 0.0f);
			transform->position += addVec.Rotate(transform->rotation) * 0.01f;
		}
		// �E���L�[��������Ă���H
		if (KeyInput::GetKeyDown(RightArrow))
		{
			Vector3 addVec = Vector3(1.0f, 0.0f, 0.0f);
			transform->position += addVec.Rotate(transform->rotation) * 0.01f;
		}
	}

	// ----- �J������] ----- //
	// �E�N���b�N��������Ă���H
	if (MouseInput::GetMouseDown(RightButton))
	{
		// �J�[�\���̈ړ��ʂɍ��킹�ăJ��������]
		Vector2 moveAmount = PublicSystem::MouseInput::GetCursorMoveAmount();
		transform->rotation.x -= moveAmount.y * 0.01f * PublicSystem::Time::DeltaTime;
		transform->rotation.y += moveAmount.x * 0.01f * PublicSystem::Time::DeltaTime;
	}

	// ===== �N���b�N�����I�u�W�F�N�g���擾 ===== //
	static bool isTextMove = false;
	bool isObjectClicked = false;	// �I�u�W�F�N�g���N���b�N���ꂽ���ǂ���
	// ���N���b�N���ꂽ�H
	if (MouseInput::GetMouseDownTrigger(LeftButton))
	{
		// �N���b�N�����I�u�W�F�N�g���ꎞ�I�ɑ������ϐ�
		GameObject* tmpClickedObject;

		// �G�f�B�b�g�V�[�����Q�Ƃ��āA�N���b�N���ꂽ�I�u�W�F�N�g���擾
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointManipulator(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		// �I�u�W�F�N�g���N���b�N���ꂽ�H
		if (tmpClickedObject)
		{
			m_clickedManipulator = tmpClickedObject;	// �N���b�N���ꂽ�I�u�W�F�N�g����
			return;	// �X�V�����I��
		}

		// ���݂̃V�[�����Q�Ƃ��āA�N���b�N���ꂽ�I�u�W�F�N�g���擾
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		// �N���b�N���ꂽ�I�u�W�F�N�g�����b�N����Ă����珈�����I��
		if (tmpClickedObject && Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->IsRockObject(tmpClickedObject->GetName()))
			return;

		// ----- ���݂̃N���b�N��Ԃɂ���ď����𕪊� ----- //
		// �ʂ̃I�u�W�F�N�g���N���b�N���ꂽ�H
		if (tmpClickedObject && m_clickedObject && tmpClickedObject != m_clickedObject)
		{
			// �e�L�X�g�R���|�[�l���g�������Ă���H
			if (m_clickedObject->GetComponent<Text>())
			{
				// �e�L�X�g�������Ă��Ȃ���Ԃŉ������ꂽ�H
				if (strcmp(m_clickedObject->GetComponent<Text>()->text, "") == 0)
					m_clickedObject->Destroy();	// �폜
			}

			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_clickedObject = tmpClickedObject;
			// �N���b�N���ꂽ���Ƃ�`����
			isObjectClicked = true;

			// ----- ���M����l���� ----- //
			// �C���X�^���X����
			MessageData messageData;
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::ClickObject;
			// �I�u�W�F�N�g
			messageData.message.body.object.CopyName(m_clickedObject->GetName());
			
			// ���b�Z�[�W�𑗂鏈�������s
			PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
		// �I�u�W�F�N�g���N���b�N���ꂽ�H
		else if (tmpClickedObject)
		{
			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_clickedObject = tmpClickedObject;
			// �N���b�N���ꂽ���Ƃ�`����
			isObjectClicked = true;

			// ----- ���M����l���� ----- //
			// �C���X�^���X����
			MessageData messageData;
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::ClickObject;
			// �I�u�W�F�N�g
			messageData.message.body.object.CopyName(m_clickedObject->GetName());

			// ���b�Z�[�W�𑗂鏈�������s
			PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
		// �I�u�W�F�N�g���������ꂽ�H
		else if (!tmpClickedObject && m_clickedObject)
		{
			// �e�L�X�g�R���|�[�l���g�������Ă���H
			if (m_clickedObject->GetComponent<Text>())
			{
				// �e�L�X�g�������Ă��Ȃ���Ԃŉ������ꂽ�H
				if (strcmp(m_clickedObject->GetComponent<Text>()->text, "") == 0)
					m_clickedObject->Destroy();	// �폜
			}

			// �N���b�N�I�u�W�F�N�g������
			m_clickedObject = nullptr;

			// ----- ���M����l���� ----- //
			// �C���X�^���X����
			MessageData messageData;
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::ClickObject;
			// �I�u�W�F�N�g
			messageData.message.body.object.CopyName(nullptr);

			// ���b�Z�[�W�𑗂鏈�������s
			PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}
	// �e�L�X�g�I�u�W�F�N�g�������ꂽ�H
	else if (MouseInput::GetMouseUp(LeftButton) && m_clickedObject && m_clickedObject->GetComponent<Text>())
	{
		// �e�L�X�g�ړ������s�ł��Ȃ��悤�ɂ���
		isTextMove = false;
	}
	// �}�j�s�����[�^�[�������ꂽ�H
	else if (MouseInput::GetMouseUp(LeftButton) && m_clickedManipulator)
	{
		m_clickedManipulator = nullptr;
	}

	// ===== �N���b�N�����I�u�W�F�N�g�̑��� ===== //
	// �I�u�W�F�N�g���擾���Ă���H
	if (m_clickedObject)
	{
		if (KeyInput::GetKeyDown(W))
			m_clickedObject->transform->position.z += 0.01f;
		if (KeyInput::GetKeyDown(A))
			m_clickedObject->transform->position.x -= 0.01f;
		if (KeyInput::GetKeyDown(S))
			m_clickedObject->transform->position.z -= 0.01f;
		if (KeyInput::GetKeyDown(D))
			m_clickedObject->transform->position.x += 0.01f;

		// �e�L�X�g�R���|�[�l���g�������Ă���H
		if (m_clickedObject->GetComponent<Text>())
		{
			// ===== �e�L�X�g�ړ����� ===== //
			static Vector2 startCursorPosition;		// �����J�n���̃N���b�N���W 
			static Vector2 startLeftTopPoint;		// �����J�n���̍�����W
			// ���݂̃J�[�\�����W
			Vector2 nowCursorPosition = MouseInput::GetCursorPosition();

			// �e�L�X�g���N���b�N���ꂽ�u�ԁH
			if (isObjectClicked)
			{
				// �J�n���Ɏ擾��������擾
				isTextMove = true;
				startCursorPosition = nowCursorPosition;
				startLeftTopPoint = m_clickedObject->GetComponent<Text>()->leftTopPoint;
			}
			// �e�L�X�g�ړ����������s�ł���H
			else if(isTextMove)
			{
				// �e�L�X�g�̍�����W���v�Z
				m_clickedObject->GetComponent<Text>()->leftTopPoint = startLeftTopPoint + (nowCursorPosition - startCursorPosition);
			}

			// ===== �e�L�X�g�̃t�H���g�T�C�Y�̊g��E�k�� ===== //
			// �}�E�X�z�C�[�����O����]���ꂽ�H
			if (MouseInput::GetWheelRotationForward())
			{
				// �t�H���g�T�C�Y���g�傷��
				m_clickedObject->GetComponent<Text>()->fontSize *= 1.1f;
			}
			// �}�E�X�z�C�[���������]���ꂽ�H
			else if (MouseInput::GetWheelRotationBackward())
			{
				// �t�H���g�T�C�Y���k������
				m_clickedObject->GetComponent<Text>()->fontSize *= 0.9f;
			}
		}
	}	
}

Ctlan::PrivateSystem::GameObject* Ctlan::EngineObject::SpectatorCamera::GetClickedObject() const
{
	return m_clickedObject;
}

Ctlan::PrivateSystem::GameObject* Ctlan::EngineObject::SpectatorCamera::GetClickedManipulator() const
{
	return m_clickedManipulator;
}
