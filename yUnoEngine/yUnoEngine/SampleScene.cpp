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
    AddSceneObject<SpectatorCamera>(0);
    AddSceneObject<Test>(1);
    AddSceneObject<Test2>(1);
}

void SampleScene::Update()
{
    // KeyInput�̃e�X�g�FLShift�������ꂽ�H
    if (KeyInput::GetKeyDownTrigger(KeyName::LeftShift))
    {
        std::cout << "Pushed LShift" << std::endl;
    }

    // KeyInput�̃e�X�g�FRShift�������ꂽ�H
    if (KeyInput::GetKeyDownTrigger(KeyName::RightShift))
    {
        std::cout << "Pushed RShift" << std::endl;
    }
}
