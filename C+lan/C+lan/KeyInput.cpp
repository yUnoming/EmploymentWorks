// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "KeyInput.h"
#include "SystemKeyInputManager.h"
#include "InputPartsName.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
class SystemKeyInputManager;

bool Ctlan::PublicSystem::KeyInput::GetKeyDownTrigger(KeyName key)
{
	return PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyDownTrigger(key);
}

bool Ctlan::PublicSystem::KeyInput::GetKeyDown(KeyName key)
{
	return PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyDown(key);
}

double Ctlan::PublicSystem::KeyInput::GetKeyDownTime(KeyName key)
{
	return PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyDownTime(key);
}

bool Ctlan::PublicSystem::KeyInput::GetKeyUpTrigger(KeyName key)
{
	return PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyUpTrigger(key);
}

bool Ctlan::PublicSystem::KeyInput::GetKeyUp(KeyName key)
{
	return PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyUp(key);
}

double Ctlan::PublicSystem::KeyInput::GetKeyUpTime(KeyName key)
{
	return PrivateSystem::SystemManager::SystemKeyInputManager::GetKeyUpTime(key);
}