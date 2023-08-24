#include "SampleScene.h"
#include "GameObject.h"
#include "KeyInput.h"
#include "InputPartsName.h"
#include "modelRenderer.h"
#include "Transform.h"
#include "SpectatorCamera.h"

#include "Test.h"
#include <iostream>

using namespace PublicSystem;

void SampleScene::Init()
{
    AddObject<SpectatorCamera>(0);
    Test* test = AddObject<Test>(1);
}

void SampleScene::Update()
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
