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
    // マウスが押された瞬間ならtrueを返す
    return yUno_MouseInputManager::Now_MouseStatus[_mb] == DOWN && 
        (yUno_MouseInputManager::Late_MouseStatus[_mb] == UP || yUno_MouseInputManager::Late_MouseStatus[_mb] == NOSTATUS);
}

bool PublicSystem::MouseInput::GetMouseDown(MouseButtonName _mb)
{
    // マウスが押されていたらtrueを返す
    return yUno_MouseInputManager::Now_MouseStatus[_mb] == DOWN;
}
