// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "MouseInput.h"
#include "SystemMouseInputManager.h"
#include "Vector2.h"

#include <d3d11.h>


Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::MouseInput::GetCursorPosition()
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetNowCursorPosition();
}

Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::MouseInput::GetCursorMoveAmount()
{
    Vector2 moveAmount = Vector2(
        PrivateSystem::SystemManager::SystemMouseInputManager::GetNowCursorPosition().x - PrivateSystem::SystemManager::SystemMouseInputManager::GetLateCursorPosition().x,
        PrivateSystem::SystemManager::SystemMouseInputManager::GetLateCursorPosition().y - PrivateSystem::SystemManager::SystemMouseInputManager::GetNowCursorPosition().y
    );
    return moveAmount;
}

bool Ctlan::PublicSystem::MouseInput::GetMouseDownTrigger(Ctlan::PublicSystem::MouseButtonName button)
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseDownTrigger(button);
}

bool Ctlan::PublicSystem::MouseInput::GetMouseDown(Ctlan::PublicSystem::MouseButtonName button)
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseDown(button);
}

bool Ctlan::PublicSystem::MouseInput::GetMouseUpTrigger(Ctlan::PublicSystem::MouseButtonName button)
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseUpTrigger(button);
}

bool Ctlan::PublicSystem::MouseInput::GetMouseUp(Ctlan::PublicSystem::MouseButtonName button)
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetMouseUp(button);
}

bool Ctlan::PublicSystem::MouseInput::GetWheelRotation()
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotation();
}

bool Ctlan::PublicSystem::MouseInput::GetWheelRotationForward()
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotationForward();
}

bool Ctlan::PublicSystem::MouseInput::GetWheelRotationBackward()
{
    return PrivateSystem::SystemManager::SystemMouseInputManager::GetWheelRotationBackward();
}