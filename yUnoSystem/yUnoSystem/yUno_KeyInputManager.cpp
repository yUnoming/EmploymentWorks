// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_KeyInputManager.h"
#include "KeyInput.h"
#include "Time.h"

#include <Windows.h>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
yUno_SystemManager::KEY_INFO yUno_SystemManager::yUno_KeyInputManager::Now_KeyInfo[400];
yUno_SystemManager::KEY_INFO yUno_SystemManager::yUno_KeyInputManager::Late_KeyInfo[400];
std::vector<int> yUno_SystemManager::yUno_KeyInputManager::Down_KeyType[400];
std::vector<int> yUno_SystemManager::yUno_KeyInputManager::Up_KeyType[400];
int yUno_SystemManager::yUno_KeyInputManager::Down_KeyType_Index;
int yUno_SystemManager::yUno_KeyInputManager::Up_KeyType_Index;


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
//	　　　　　グローバル宣言			//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// このCPP内でKeyInputの変数を使用するためにグローバル宣言
System::KeyInput g_KeyInput;


void yUno_SystemManager::yUno_KeyInputManager::Update()
{
	// ＝＝＝＝＝ 各キー状態の経過時間を測定 ＝＝＝＝＝ //
	// ＊ 押されているキー ＊ //
	// キーが押されている？（押されていない場合は処理を行わない）
	if (!Down_KeyType->empty())
	{
		// 押されているキーの数だけループ
		for (int i = 0; i < Down_KeyType_Index; i++)
		{
			// キーの押されている時間を計算
			Now_KeyInfo[Down_KeyType->at(i)].KeyState_ElapsedTime += System::Time::DeltaTime * 0.0001f;
		}
	}
	// ＊ 離されているキー ＊ //
	// キーが離されている（判定を行っているキーが存在する）？（離されていない（判定を行っているキーが存在しない）場合は処理を行わない）
	if (!Up_KeyType->empty())
	{
		// 離されているキーの数だけループ
		for (int i = 0; i < Up_KeyType_Index; i++)
		{
			// キーの離されている時間を計算
			Now_KeyInfo[Up_KeyType->at(i)].KeyState_ElapsedTime += System::Time::DeltaTime * 0.0001f;
		}
	}
}

void yUno_SystemManager::yUno_KeyInputManager::Keep_Now_KeyInfo()
{
	// 現在のキー状態を保存
	memcpy(Late_KeyInfo, Now_KeyInfo, sizeof(Now_KeyInfo));
}

void yUno_SystemManager::yUno_KeyInputManager::Set_KeyDown(int _key)
{
	// ＝＝＝＝＝　判定のリセット処理　＝＝＝＝＝ //
	// 離された判定の途中でキーが押された？
	if (Now_KeyInfo[_key].KeyState == Up)
	{
		// 離れているキーの判定から除外
		Up_KeyType->erase(std::find(Up_KeyType->begin(), Up_KeyType->end(), _key));

		// 要素数を減らす
		Up_KeyType_Index--;

		// 経過時間をリセット
		Now_KeyInfo[_key].KeyState_ElapsedTime = 0.0;
	}

	// ＝＝＝＝＝　押されたキーの処理　＝＝＝＝＝ //
	// 前回キーは離されていた？
	if (Now_KeyInfo[_key].KeyState != Down)
	{
		// キーが押されていることを保存
		Now_KeyInfo[_key].KeyState = Down;

		// 押されているキーの種類を保存
		Down_KeyType->emplace_back(_key);

		// 要素数を増やす
		Down_KeyType_Index++;
	}
	else
	{
		int a = 0;
		a = a;
	}
}

void yUno_SystemManager::yUno_KeyInputManager::Set_KeyUp(int _key)
{
	// ＝＝＝＝＝　判定の変更処理　＝＝＝＝＝ //
	// 前回キーは押されていた？
	if (Now_KeyInfo[_key].KeyState == Down)
	{
		// 離れているキーの判定から除外
		Down_KeyType->erase(std::find(Down_KeyType->begin(), Down_KeyType->end(), _key));

		// 要素数を減らす
		Down_KeyType_Index--;

		// 経過時間をリセット
		Now_KeyInfo[_key].KeyState_ElapsedTime = 0.0;


		// ＝＝＝＝＝　押されたキーの処理　＝＝＝＝＝ //
		// キーが離されていることを保存
		Now_KeyInfo[_key].KeyState = Up;

		// 離されたキーの種類を保存
		Up_KeyType->emplace_back(_key);

		// 要素数を増やす
		Up_KeyType_Index++;
	}
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Trigger(System::KeyName _key)
{
	// 前回キーは離されていたが、現在は押されている？
	if (Late_KeyInfo[_key].KeyState != Down && Now_KeyInfo[_key].KeyState == Down)
		return true;
	return false;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyDown(System::KeyName _key)
{
	// 現在キーは押されている？
	if (Now_KeyInfo[_key].KeyState == Down)
		return true;
	return false;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyDown_Time(System::KeyName _key)
{
	// キーが押されている？
	if (Now_KeyInfo[_key].KeyState == Down)
	{
		return Now_KeyInfo[_key].KeyState_ElapsedTime;
	}

	return 0;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Trigger(System::KeyName _key)
{
	// 前回キーは押されていたが、現在は離されている？
	if (Late_KeyInfo[_key].KeyState == Down && Now_KeyInfo[_key].KeyState != Down)
		return true;
	return false;
}

bool yUno_SystemManager::yUno_KeyInputManager::GetKeyUp(System::KeyName _key)
{
	// 現在キーは離されている？
	if (Now_KeyInfo[_key].KeyState == NoStatus || Now_KeyInfo[_key].KeyState == Up)
		return true;
	return false;
}

double yUno_SystemManager::yUno_KeyInputManager::GetKeyUp_Time(System::KeyName _key)
{
	// キーが離されている？
	if (Now_KeyInfo[_key].KeyState == Up)
	{
		return Now_KeyInfo[_key].KeyState_ElapsedTime;
	}

	return 0;
}
