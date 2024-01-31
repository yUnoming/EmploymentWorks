#include "SceneManager.h"

std::array<std::list<Ctlan::PrivateSystem::GameObject*>, 4> Ctlan::PublicSystem::SceneManager::GetSceneObjectAll()
{
	return m_loadedScene->GetAllSceneObjects();
}
Ctlan::PrivateSystem::SceneBase* Ctlan::PublicSystem::SceneManager::GetNowScene()
{
	return m_loadedScene;
}

void Ctlan::PublicSystem::SceneManager::LoadScene(const char* sceneName)
{
	strcpy_s(loadSceneName, sceneName);
}
