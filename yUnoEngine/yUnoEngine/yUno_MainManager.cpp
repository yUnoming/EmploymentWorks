// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <Windows.h>

#include "yUno_MainManager.h"
#include "yUno_TimeManager.h"
#include "yUno_KeyInputManager.h"

#include "KeyInput.h"
#include "KeyName.h"
#include <iostream>

// ������������������������������ //
// �@�@		 using�錾 	    	  //
// ������������������������������ //
using namespace yUno_SystemManager;
using namespace System;


void yUno_MainManager::Init()
{
    // ���������� �V�X�e���̏��������� ���������� //
    // ����
    yUno_TimeManager::Init();
}

void yUno_MainManager::UnInit()
{
}

void yUno_MainManager::Update()
{
    // ���������� �V�X�e�������̍X�V���� ���������� //
    // ����
    yUno_TimeManager::Update();

    // �L�[����
    yUno_KeyInputManager::Update();

    // ���������� �G���W���̍X�V���� ���������� //
    // KeyInput�̃e�X�g�FLShift�������ꂽ�H
    if (KeyInput::GetKeyDown_Trigger(KeyName::LeftShift))
    {
        std::cout << "Pushed LShift" << std::endl;
    }

    // KeyInput�̃e�X�g�FRShift�������ꂽ�H
    if (KeyInput::GetKeyDown_Trigger(KeyName::RightShift))
    {
        std::cout << "Pushed RShift" << std::endl;
    }

    // ���݂̃L�[���͏�Ԃ�ۑ�����
    yUno_KeyInputManager::Keep_Now_KeyInfo();
}

void yUno_MainManager::Draw()
{
}

void yUno_MainManager::Change_Mode()
{

}


