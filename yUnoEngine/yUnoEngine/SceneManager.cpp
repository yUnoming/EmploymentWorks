#include "SceneManager.h"

std::array<std::list<GameObject*>, 4> PublicSystem::SceneManager::GetSceneObjectAll()
{
	return m_loadedScene->GetAllSceneObjects();
}
SceneBase* PublicSystem::SceneManager::GetNowScene()
{
	return m_loadedScene;
}
