// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "KeyInput.h"
#include "yUno_KeyInputManager.h"
#include "KeyName.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
class yUno_KeyInputManager;

bool System::KeyInput::GetKeyDown_Trigger(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Trigger(_key);
}

bool System::KeyInput::GetKeyDown(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDown(_key);
}

double System::KeyInput::GetKeyDown_Time(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Time(_key);
}

bool System::KeyInput::GetKeyUp_Trigger(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Trigger(_key);
}

bool System::KeyInput::GetKeyUp(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUp(_key);
}

double System::KeyInput::GetKeyUp_Time(KeyName _key)
{
	return yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Time(_key);
}
