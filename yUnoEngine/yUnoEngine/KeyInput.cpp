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

bool PublicSystem::KeyInput::GetKeyDownTrigger(KeyName key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDownTrigger(key);
}

bool PublicSystem::KeyInput::GetKeyDown(KeyName key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDown(key);
}

double PublicSystem::KeyInput::GetKeyDownTime(KeyName key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDownTime(key);
}

bool PublicSystem::KeyInput::GetKeyUpTrigger(KeyName key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUpTrigger(key);
}

bool PublicSystem::KeyInput::GetKeyUp(KeyName key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUp(key);
}

double PublicSystem::KeyInput::GetKeyUpTime(KeyName key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUpTime(key);
}
