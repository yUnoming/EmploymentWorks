// ������������������������������������ //
// �@�@   �t�@�C���̃C���N���[�h        //
// ������������������������������������ //
#include "yUno_MouseInputManager.h"

#include <Windows.h>


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
yUno_SystemManager::MOUSE_STATE yUno_SystemManager::yUno_MouseInputManager::Now_MouseStatus[3];
yUno_SystemManager::MOUSE_STATE yUno_SystemManager::yUno_MouseInputManager::Late_MouseStatus[3];


void yUno_SystemManager::yUno_MouseInputManager::Keep_Now_MouseStatus()
{
	// ���݂̃}�E�X�̏�Ԃ�ۑ�
	memcpy(Late_MouseStatus, Now_MouseStatus, sizeof(Now_MouseStatus));
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseDown(PublicSystem::MouseButtonName _mb)
{
	// �}�E�X��������Ă����ԂɕύX
	Now_MouseStatus[_mb] = yUno_SystemManager::DOWN;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseUp(PublicSystem::MouseButtonName _mb)
{
	// �}�E�X��������Ă����ԂɕύX
	Now_MouseStatus[_mb] = yUno_SystemManager::UP;
}
