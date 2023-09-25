// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "yUno_MouseInputManager.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
yUno_SystemManager::MOUSE_STATUS yUno_SystemManager::yUno_MouseInputManager::Now_Mouse_Status[3];
yUno_SystemManager::MOUSE_STATUS yUno_SystemManager::yUno_MouseInputManager::Late_Mouse_Status[3];
yUno_SystemManager::MOUSEWHEEL_STATUS yUno_SystemManager::yUno_MouseInputManager::MouseWheel_Status;


void yUno_SystemManager::yUno_MouseInputManager::Keep_Now_MouseStatus()
{
	// ���݂̃}�E�X�̏�Ԃ��Z�b�g
	memcpy(Late_Mouse_Status, Now_Mouse_Status, sizeof(Now_Mouse_Status));
	
	// �}�E�X�z�C�[���̉�]������I��
	MouseWheel_Status = NOT_ROTATION;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseDown(PublicSystem::MouseButtonName _mb)
{
	// �}�E�X��������Ă����ԂɕύX
	Now_Mouse_Status[_mb] = yUno_SystemManager::DOWN;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseUp(PublicSystem::MouseButtonName _mb)
{
	// �}�E�X��������Ă����ԂɕύX
	Now_Mouse_Status[_mb] = yUno_SystemManager::UP;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseWheel_Status(int _wheelParam)
{
	// ���݂̃}�E�X�z�C�[���̓��͒l���Z�b�g
	MouseWheel_Status = (MOUSEWHEEL_STATUS)_wheelParam;
}