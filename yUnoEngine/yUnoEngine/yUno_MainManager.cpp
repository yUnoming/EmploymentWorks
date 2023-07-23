// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <Windows.h>

#include "yUno_MainManager.h"
#include "yUno_TimeManager.h"
#include "yUno_KeyInputManager.h"

#include "KeyInput.h"
#include "KeyName.h"
#include <iostream>

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 using宣言 	    	  //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace yUno_SystemManager;
using namespace System;


void yUno_MainManager::Init()
{
    // ＝＝＝＝＝ システムの初期化処理 ＝＝＝＝＝ //
    // 時間
    yUno_TimeManager::Init();
}

void yUno_MainManager::UnInit()
{
}

void yUno_MainManager::Update()
{
    // ＝＝＝＝＝ システム内部の更新処理 ＝＝＝＝＝ //
    // 時間
    yUno_TimeManager::Update();

    // キー入力
    yUno_KeyInputManager::Update();

    // ＝＝＝＝＝ エンジンの更新処理 ＝＝＝＝＝ //
    // KeyInputのテスト：LShiftが押された？
    if (KeyInput::GetKeyDown_Trigger(KeyName::LeftShift))
    {
        std::cout << "Pushed LShift" << std::endl;
    }

    // KeyInputのテスト：RShiftが押された？
    if (KeyInput::GetKeyDown_Trigger(KeyName::RightShift))
    {
        std::cout << "Pushed RShift" << std::endl;
    }

    // 現在のキー入力状態を保存する
    yUno_KeyInputManager::Keep_Now_KeyInfo();
}

void yUno_MainManager::Draw()
{
}

void yUno_MainManager::Change_Mode()
{

}


