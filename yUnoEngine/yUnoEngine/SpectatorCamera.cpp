// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
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
	if (MouseInput::GetMouseDown_Trigger(LeftButton))
	{
		// �N���b�N�����I�u�W�F�N�g���ꎞ�I�ɑ������ϐ�
		GameObject* Tmp_Clicked_Object;

		// �N���b�N�����ʒu�ɃI�u�W�F�N�g������ꍇ�A���̃I�u�W�F�N�g���擾
		// �擾���ꂽ��ԂŃI�u�W�F�N�g���Ȃ��ꏊ���N���b�N���ꂽ��A�擾����������
		Tmp_Clicked_Object = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		
		// �ʂ̃I�u�W�F�N�g���N���b�N���ꂽ�H
		if (m_Clicked_Object && Tmp_Clicked_Object != m_Clicked_Object)
		{
			// �N���b�N����Ă����I�u�W�F�N�g�̃}�e���A����ύX
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			
			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_Clicked_Object = Tmp_Clicked_Object;
			// �N���b�N���ꂽ�I�u�W�F�N�g�̃}�e���A����ύX
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		}
		// �I�u�W�F�N�g���N���b�N���ꂽ�H
		else if (Tmp_Clicked_Object)
		{
			// �N���b�N���ꂽ�I�u�W�F�N�g�������o�ϐ��ɑ��
			m_Clicked_Object = Tmp_Clicked_Object;
			// �N���b�N���ꂽ�I�u�W�F�N�g�̃}�e���A����ύX
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		}
		// �I�u�W�F�N�g���������ꂽ�H
		else if (!Tmp_Clicked_Object && m_Clicked_Object)
		{
			// �N���b�N����Ă����I�u�W�F�N�g�̃}�e���A����ύX
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}


	// ===== �N���b�N�����I�u�W�F�N�g�̑��� ===== //
	// �I�u�W�F�N�g���擾���Ă���H
	if (m_Clicked_Object)
	{
		if (KeyInput::GetKeyDown(W))
			m_Clicked_Object->transform->Position.z += 0.01f;
		if (KeyInput::GetKeyDown(A))
			m_Clicked_Object->transform->Position.x -= 0.01f;
		if (KeyInput::GetKeyDown(S))
			m_Clicked_Object->transform->Position.z -= 0.01f;
		if (KeyInput::GetKeyDown(D))
			m_Clicked_Object->transform->Position.x += 0.01f;

	}
		
}
