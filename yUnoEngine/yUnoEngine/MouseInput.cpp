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
    GetCursorPos(&CursorPos);

    Return_CursorPos.x = CursorPos.x;
    Return_CursorPos.y = CursorPos.y;

    return Return_CursorPos;
}

bool PublicSystem::MouseInput::GetMouseDown_Trigger(MouseButtonName _mb)
{
    // マウスが押された瞬間なら””true””を返す
    return yUno_MouseInputManager::Now_Mouse_Status[_mb] == DOWN && 
        (yUno_MouseInputManager::Late_Mouse_Status[_mb] == UP || yUno_MouseInputManager::Late_Mouse_Status[_mb] == NOSTATUS);
}

bool PublicSystem::MouseInput::GetMouseDown(MouseButtonName _mb)
{
    // マウスが押されていたら””true””を返す
    return yUno_MouseInputManager::Now_Mouse_Status[_mb] == DOWN;
}

bool PublicSystem::MouseInput::GetWheelRotation()
{
    // マウスホイールが回転されていたら””true””を返す
    return yUno_MouseInputManager::MouseWheel_Status == FORWARD_ROTATION || yUno_MouseInputManager::MouseWheel_Status == BACKWARD_ROTATION;
}

bool PublicSystem::MouseInput::GetWheelRotation_Forward()
{
    // マウスホイールが前方回転されていたら””true””を返す
    return yUno_MouseInputManager::MouseWheel_Status == FORWARD_ROTATION;
}

bool PublicSystem::MouseInput::GetWheelRotation_Backward()
{
    // マウスホイールが後方回転されていたら””true””を返す
    return yUno_MouseInputManager::MouseWheel_Status == BACKWARD_ROTATION;
}
