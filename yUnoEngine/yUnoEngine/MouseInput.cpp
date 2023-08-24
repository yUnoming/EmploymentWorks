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
    // �}�E�X�������ꂽ�u�ԂȂ�true��Ԃ�
    return yUno_MouseInputManager::Now_MouseStatus[_mb] == DOWN && 
        (yUno_MouseInputManager::Late_MouseStatus[_mb] == UP || yUno_MouseInputManager::Late_MouseStatus[_mb] == NOSTATUS);
}

bool PublicSystem::MouseInput::GetMouseDown(MouseButtonName _mb)
{
    // �}�E�X��������Ă�����true��Ԃ�
    return yUno_MouseInputManager::Now_MouseStatus[_mb] == DOWN;
}
