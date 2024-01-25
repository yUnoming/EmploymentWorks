// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "SystemMouseInputManager.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::MouseStatus Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_nowMouseState[3];
Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::MouseStatus Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_lateMouseState[3];
Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::MouseWheelStatus Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_mouseWheelState;
Ctlan::PublicSystem::Vector2 Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_lateCursorPosition;
Ctlan::PublicSystem::Vector2 Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::m_nowCursorPosition;


void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::Update()
{
	// �O��̃J�[�\�����W��ۑ�
	m_lateCursorPosition = m_nowCursorPosition;
	// ���݂̃J�[�\�����W���擾
	tagPOINT cursorPos;
	GetCursorPos(&cursorPos);
	m_nowCursorPosition = PublicSystem::Vector2(cursorPos);
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::KeepNowMouseState()
{
	// ���݂̃}�E�X�̏�Ԃ��Z�b�g
	memcpy(m_lateMouseState, m_nowMouseState, sizeof(m_nowMouseState));
	
	// �}�E�X�z�C�[���̉�]������I��
	m_mouseWheelState = NotRotation;
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseDown(Ctlan::PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă����ԂɕύX
	m_nowMouseState[button] = Down;
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseUp(Ctlan::PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă����ԂɕύX
	m_nowMouseState[button] = Up;
}

void Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseWheelState(int mouseWheelParam)
{
	// ���݂̃}�E�X�z�C�[���̓��͒l���Z�b�g
	m_mouseWheelState = (MouseWheelStatus)mouseWheelParam;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseDownTrigger(Ctlan::PublicSystem::MouseButtonName button)
{
	// �}�E�X�������ꂽ�u�ԂȂ�true
	return m_nowMouseState[button] == Down &&
		(m_lateMouseState[button] == Up || m_lateMouseState[button] == NoStatus);
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseDown(Ctlan::PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă�����true
	return m_nowMouseState[button] == Down;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseUpTrigger(Ctlan::PublicSystem::MouseButtonName button)
{
	// �}�E�X�������ꂽ�u�ԂȂ�true
	return m_nowMouseState[button] == Up &&
		(m_lateMouseState[button] == Down || m_lateMouseState[button] == NoStatus);
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseUp(Ctlan::PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă�����true
	return m_nowMouseState[button] == Up || m_nowMouseState[button] == NoStatus;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotation()
{
	// �}�E�X�z�C�[������]����Ă�����true
	return m_mouseWheelState == ForwardRotation || m_mouseWheelState == BackwardRotation;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotationForward()
{
	// �}�E�X�z�C�[�����O����]����Ă�����true
	return m_mouseWheelState == ForwardRotation;
}

bool Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotationBackward()
{
	// �}�E�X�z�C�[���������]����Ă�����true
	return m_mouseWheelState == BackwardRotation;
}