// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_MouseInputManager.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
yUno_SystemManager::MOUSE_STATE yUno_SystemManager::yUno_MouseInputManager::Now_MouseStatus[3];
yUno_SystemManager::MOUSE_STATE yUno_SystemManager::yUno_MouseInputManager::Late_MouseStatus[3];


void yUno_SystemManager::yUno_MouseInputManager::Keep_Now_MouseStatus()
{
	// 現在のマウスの状態を保存
	memcpy(Late_MouseStatus, Now_MouseStatus, sizeof(Now_MouseStatus));
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseDown(PublicSystem::MouseButtonName _mb)
{
	// マウスが押されている状態に変更
	Now_MouseStatus[_mb] = yUno_SystemManager::DOWN;
}

void yUno_SystemManager::yUno_MouseInputManager::Set_MouseUp(PublicSystem::MouseButtonName _mb)
{
	// マウスが離されている状態に変更
	Now_MouseStatus[_mb] = yUno_SystemManager::UP;
}
