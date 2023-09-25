// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_MouseInputManager.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
yUno_SystemManager::MOUSE_STATUS yUno_SystemManager::yUno_MouseInputManager::Now_Mouse_Status[3];
yUno_SystemManager::MOUSE_STATUS yUno_SystemManager::yUno_MouseInputManager::Late_Mouse_Status[3];
yUno_SystemManager::MOUSEWHEEL_STATUS yUno_SystemManager::yUno_MouseInputManager::MouseWheel_Status;


void yUno_SystemManager::yUno_MouseInputManager::Keep_Now_MouseStatus()
{
	// 現在のマウスの状態をセット
	memcpy(Late_Mouse_Status, Now_Mouse_Status, sizeof(Now_Mouse_Status));
	
	// マウスホイールの回転判定を終了
	MouseWheel_Status = NOT_ROTATION;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseDown(PublicSystem::MouseButtonName _mb)
{
	// マウスが押されている状態に変更
	Now_Mouse_Status[_mb] = yUno_SystemManager::DOWN;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseUp(PublicSystem::MouseButtonName _mb)
{
	// マウスが離されている状態に変更
	Now_Mouse_Status[_mb] = yUno_SystemManager::UP;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseWheel_Status(int _wheelParam)
{
	// 現在のマウスホイールの入力値をセット
	MouseWheel_Status = (MOUSEWHEEL_STATUS)_wheelParam;
}