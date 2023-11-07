// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "MouseInput.h"
#include "yUno_MouseInputManager.h"
#include "Vector2.h"

#include <d3d11.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　       using宣言         　//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace yUno_SystemManager;


PublicSystem::Vector2 PublicSystem::MouseInput::GetCursorPosition()
{
    Vector2 Return_CursorPos;   // Vector2で値を返すための変数
    POINT CursorPos;
    GetCursorPos(&CursorPos);   // カーソル座標を取得

    // 値代入
    Return_CursorPos.x = CursorPos.x;
    Return_CursorPos.y = CursorPos.y;

    return Return_CursorPos;
}

bool PublicSystem::MouseInput::GetMouseDownTrigger(PublicSystem::MouseButtonName button)
{
    return yUno_MouseInputManager::GetMouseDownTrigger(button)
}

bool PublicSystem::MouseInput::GetMouseDown(PublicSystem::MouseButtonName button)
{
    return yUno_MouseInputManager::GetMouseDown(button);
}

bool PublicSystem::MouseInput::GetMouseUpTrigger(PublicSystem::MouseButtonName button)
{
    return yUno_MouseInputManager::GetMouseUpTrigger(button);
}

bool PublicSystem::MouseInput::GetMouseUp(PublicSystem::MouseButtonName button)
{
    return yUno_MouseInputManager::GetMouseUp(button);
}

bool PublicSystem::MouseInput::GetWheelRotation()
{
    return yUno_MouseInputManager::GetWheelRotation();
}

bool PublicSystem::MouseInput::GetWheelRotationForward()
{
    return yUno_MouseInputManager::GetWheelRotationForward();
}

bool PublicSystem::MouseInput::GetWheelRotationBackward()
{
    return yUno_MouseInputManager::GetWheelRotationBackward();
}
