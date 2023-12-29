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
		transform->position.y += 0.01f;
	if (KeyInput::GetKeyDown(LeftArrow))
		transform->position.x -= 0.01f;
	if (KeyInput::GetKeyDown(DownArrow))
		transform->position.y -= 0.01f;
	if (KeyInput::GetKeyDown(RightArrow))
		transform->position.x += 0.01f;

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
			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_clickedObject = tmpClickedObject;

			// ----- ���M����l���� ----- //
			// �C���X�^���X����
			MessageData messageData;
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::ClickObject;
			// �I�u�W�F�N�g
			messageData.message.body.object.CopyName(m_clickedObject->GetName());
			
			// ���b�Z�[�W�𑗂鏈�������s
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
		// �I�u�W�F�N�g���N���b�N���ꂽ�H
		else if (tmpClickedObject)
		{
			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_clickedObject = tmpClickedObject;

			// ----- ���M����l���� ----- //
			// �C���X�^���X����
			MessageData messageData;
			// ���b�Z�[�W�^�C�v
			messageData.message.header.type = MessageType::ClickObject;
			// �I�u�W�F�N�g
			messageData.message.body.object.CopyName(m_clickedObject->GetName());

			// ���b�Z�[�W�𑗂鏈�������s
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
		// �I�u�W�F�N�g���������ꂽ�H
		else if (!tmpClickedObject && m_clickedObject)
		{
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
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
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
	}	
}

GameObject* SpectatorCamera::GetClickedObject() const
{
	return m_clickedObject;
}
