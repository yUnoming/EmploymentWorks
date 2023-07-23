#include "yUno_SceneManager.h"

void yUno_SceneManager::InitBase()
{
	// 現在シーンのInit()を実行
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
		objectList.clear();		//リストのクリア
	}
	// 現在シーンのUnInit()を実行
	UnInit();
}

void yUno_SceneManager::UpdateBase()
{
	// 現在シーンのUodate()を実行
	Update();
}

void yUno_SceneManager::DrawBase()
{
	// 現在シーンのDraw()を実行
	Draw();
}
