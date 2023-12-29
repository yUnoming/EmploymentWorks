#include "SampleScene.h"

#include "SpectatorCamera.h"
#include "Test.h"
#include "Test2.h"
#include "Manipulator_MoveX.h"
#include <iostream>

using namespace PublicSystem;

void SampleScene::Init()
{
    if (GetSceneObject<SpectatorCamera>("SpectatorCamera") == nullptr)
    {
        AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");
    }
    if (GetSceneObject<Test2>("Text") == nullptr)
    {
        AddSceneObject<Test2>(2, "Text");
    }
    AddSceneObject<yUnoEngine::Manipulator::Manipulator_MoveX>(3, "Manipulator_MoveX");
}
