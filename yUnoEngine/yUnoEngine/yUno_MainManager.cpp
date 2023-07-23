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


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
bool yUno_MainManager::m_DemoPlay;


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
    // ----- デモプレイの切り替え----- //
    // 仮）Enterキーが押された？
    if (KeyInput::GetKeyDown_Trigger(KeyName::Enter))
        m_DemoPlay ^= true;  // デモプレイの状態を切り替える

    // デモプレイ中？
    if (m_DemoPlay)
    {
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
    }

    // 現在のキー入力状態を保存する
    yUno_KeyInputManager::Keep_Now_KeyInfo();
}

void yUno_MainManager::Draw()
{
}

