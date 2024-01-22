// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "ScreenInput.h"
#include "Vector2.h"
#include "Application.h"
#include <SimpleMath.h>
#include <Windows.h>


Ctlan::PublicSystem::Vector2 Ctlan::PublicSystem::ScreenInput::GetScreenPosition(Vector2 _paramPosition)
{
    // スクリーン座標を代入する変数（引数の値を初期値として代入）
    POINT ScreenPosition = {_paramPosition.x, _paramPosition.y};

    // スクリーン座標を取得
    ScreenToClient(PrivateSystem::Application::GetWindow(), &ScreenPosition);
    // ** 上記関数の補足 **
    // ScreenはPCの画面などの事を指し、
    // Clientはアプリの画面（ScreenInputのScreenに値するもの）を指している。

    // 値をVector2に変換して返す
    return Vector2(ScreenPosition.x, ScreenPosition.y);
}
