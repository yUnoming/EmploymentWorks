#include "SampleScene.h"
#include "GameObject.h"
#include "KeyInput.h"
#include "InputPartsName.h"
#include "modelRenderer.h"
#include "Transform.h"
#include "SpectatorCamera.h"

#include "Test.h"
#include "Test2.h"
#include <iostream>

using namespace PublicSystem;

void SampleScene::Init()
{
    if (GetSceneObject<SpectatorCamera>("SpectatorCamera") == nullptr)
    {
        AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
    }
    if (GetSceneObject<Test>("Object1") == nullptr)
    {
        AddSceneObject<Test>(1, "Object1");
    }
    if (GetSceneObject<Test2>("Text") == nullptr)
    {
        AddSceneObject<Test2>(1, "Text");
    }
    if(GetSceneObject<Test2>("Text2") == nullptr)
    {
        AddSceneObject<Test2>(1, "Text2");
    }
}

void SampleScene::Update()
{
    // KeyInputのテスト：LShiftが押された？
    if (KeyInput::GetKeyDownTrigger(KeyName::LeftShift))
    {
        std::cout << "Pushed LShift" << std::endl;
    }

    // KeyInputのテスト：RShiftが押された？
    if (KeyInput::GetKeyDownTrigger(KeyName::RightShift))
    {
        std::cout << "Pushed RShift" << std::endl;
    }
}
