// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "yUno_MouseInputManager.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
yUno_SystemManager::yUno_MouseInputManager::MouseStatus yUno_SystemManager::yUno_MouseInputManager::m_nowMouseState[3];
yUno_SystemManager::yUno_MouseInputManager::MouseStatus yUno_SystemManager::yUno_MouseInputManager::m_lateMouseState[3];
yUno_SystemManager::yUno_MouseInputManager::MouseWheelStatus yUno_SystemManager::yUno_MouseInputManager::m_mouseWheelState;


void yUno_SystemManager::yUno_MouseInputManager::KeepNowMouseState()
{
	// ���݂̃}�E�X�̏�Ԃ��Z�b�g
	memcpy(m_lateMouseState, m_nowMouseState, sizeof(m_nowMouseState));
	
	// �}�E�X�z�C�[���̉�]������I��
	m_mouseWheelState = NotRotation;
}

void yUno_SystemManager::yUno_MouseInputManager::SetMouseDown(PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă����ԂɕύX
	m_nowMouseState[button] = Down;
}

void yUno_SystemManager::yUno_MouseInputManager::SetMouseUp(PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă����ԂɕύX
	m_nowMouseState[button] = Up;
}

void yUno_SystemManager::yUno_MouseInputManager::SetMouseWheelState(int mouseWheelParam)
{
	// ���݂̃}�E�X�z�C�[���̓��͒l���Z�b�g
	m_mouseWheelState = (MouseWheelStatus)mouseWheelParam;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseDownTrigger(PublicSystem::MouseButtonName button)
{
	// �}�E�X�������ꂽ�u�ԂȂ�true
	return m_nowMouseState[button] == Down &&
		(m_lateMouseState[button] == Up || m_lateMouseState[button] == NoStatus);
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseDown(PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă�����true
	return m_nowMouseState[button] == Down;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseUpTrigger(PublicSystem::MouseButtonName button)
{
	// �}�E�X�������ꂽ�u�ԂȂ�true
	return m_nowMouseState[button] == Up &&
		(m_lateMouseState[button] == Down || m_lateMouseState[button] == NoStatus);
}

bool yUno_SystemManager::yUno_MouseInputManager::GetMouseUp(PublicSystem::MouseButtonName button)
{
	// �}�E�X��������Ă�����true
	return m_nowMouseState[button] == Up || m_nowMouseState[button] == NoStatus;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetWheelRotation()
{
	// �}�E�X�z�C�[������]����Ă�����true
	return m_mouseWheelState == ForwardRotation || m_mouseWheelState == BackwardRotation;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetWheelRotationForward()
{
	// �}�E�X�z�C�[�����O����]����Ă�����true
	return m_mouseWheelState == ForwardRotation;
}

bool yUno_SystemManager::yUno_MouseInputManager::GetWheelRotationBackward()
{
	// �}�E�X�z�C�[���������]����Ă�����true
	return m_mouseWheelState == BackwardRotation;
}