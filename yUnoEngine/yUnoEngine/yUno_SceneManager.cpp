#include "yUno_SceneManager.h"

void yUno_SceneManager::InitBase()
{
	// ���݃V�[����Init()�����s
	Init();
}

void yUno_SceneManager::UnInitBase()
{
	for (auto& objectList : m_GameObject)
	{
		for (GameObject* object : objectList)
		{
			object->UninitBase();
			delete object;
		}
		objectList.clear();		//���X�g�̃N���A
	}
	// ���݃V�[����UnInit()�����s
	UnInit();
}

void yUno_SceneManager::UpdateBase()
{
	// ���݃V�[����Uodate()�����s
	Update();
}

void yUno_SceneManager::DrawBase()
{
	// ���݃V�[����Draw()�����s
	Draw();
}
