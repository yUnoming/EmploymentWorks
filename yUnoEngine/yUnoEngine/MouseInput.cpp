//  //
// @@t@CΜCN[h@@ //
//  //
#include "MouseInput.h"
#include "yUno_MouseInputManager.h"
#include "Vector2.h"

#include <d3d11.h>


//  //
// @@       usingιΎ         @//
//  //
using namespace yUno_SystemManager;


PublicSystem::Vector2 PublicSystem::MouseInput::GetCursorPosition()
{
    Vector2 Return_CursorPos;   // Vector2ΕlπΤ·½ίΜΟ
    POINT CursorPos;
    GetCursorPos(&CursorPos);   // J[\ΐWπζΎ

    // lγό
    Return_CursorPos.x = CursorPos.x;
    Return_CursorPos.y = CursorPos.y;

    return Return_CursorPos;
}

bool PublicSystem::MouseInput::GetMouseDownTrigger(PublicSystem::MouseButtonName button)
{
    return yUno_MouseInputManager::GetMouseDownTrigger(button);
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
