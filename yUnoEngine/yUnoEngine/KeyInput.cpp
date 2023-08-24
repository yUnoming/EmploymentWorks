// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "KeyInput.h"
#include "yUno_KeyInputManager.h"
#include "InputPartsName.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
class yUno_KeyInputManager;

bool PublicSystem::KeyInput::GetKeyDown_Trigger(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Trigger(_key);
}

bool PublicSystem::KeyInput::GetKeyDown(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDown(_key);
}

double PublicSystem::KeyInput::GetKeyDown_Time(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Time(_key);
}

bool PublicSystem::KeyInput::GetKeyUp_Trigger(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Trigger(_key);
}

bool PublicSystem::KeyInput::GetKeyUp(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUp(_key);
}

double PublicSystem::KeyInput::GetKeyUp_Time(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Time(_key);
}
