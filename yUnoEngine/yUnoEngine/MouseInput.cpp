// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "MouseInput.h"
#include "yUno_MouseInputManager.h"
#include "Vector2.h"

#include <d3d11.h>


// ������������������������������ //
// �@�@       using�錾         �@//
// ������������������������������ //
using namespace yUno_SystemManager;


PublicSystem::Vector2 PublicSystem::MouseInput::GetCursorPosition()
{
    Vector2 Return_CursorPos;   // Vector2�Œl��Ԃ����߂̕ϐ�
    POINT CursorPos;
    GetCursorPos(&CursorPos);

    Return_CursorPos.x = CursorPos.x;
    Return_CursorPos.y = CursorPos.y;

    return Return_CursorPos;
}

bool PublicSystem::MouseInput::GetMouseDown_Trigger(MouseButtonName _mb)
{
    // �}�E�X�������ꂽ�u�ԂȂ�h�htrue�h�h��Ԃ�
    return yUno_MouseInputManager::Now_Mouse_Status[_mb] == DOWN && 
        (yUno_MouseInputManager::Late_Mouse_Status[_mb] == UP || yUno_MouseInputManager::Late_Mouse_Status[_mb] == NOSTATUS);
}

bool PublicSystem::MouseInput::GetMouseDown(MouseButtonName _mb)
{
    // �}�E�X��������Ă�����h�htrue�h�h��Ԃ�
    return yUno_MouseInputManager::Now_Mouse_Status[_mb] == DOWN;
}

bool PublicSystem::MouseInput::GetWheelRotation()
{
    // �}�E�X�z�C�[������]����Ă�����h�htrue�h�h��Ԃ�
    return yUno_MouseInputManager::MouseWheel_Status == FORWARD_ROTATION || yUno_MouseInputManager::MouseWheel_Status == BACKWARD_ROTATION;
}

bool PublicSystem::MouseInput::GetWheelRotation_Forward()
{
    // �}�E�X�z�C�[�����O����]����Ă�����h�htrue�h�h��Ԃ�
    return yUno_MouseInputManager::MouseWheel_Status == FORWARD_ROTATION;
}

bool PublicSystem::MouseInput::GetWheelRotation_Backward()
{
    // �}�E�X�z�C�[���������]����Ă�����h�htrue�h�h��Ԃ�
    return yUno_MouseInputManager::MouseWheel_Status == BACKWARD_ROTATION;
}
