#include "SceneManager.h"

std::array<std::list<Ctlan::PrivateSystem::GameObject*>, 4> Ctlan::PublicSystem::SceneManager::GetSceneObjectAll()
{
	return m_loadedScene->GetAllSceneObjects();
}
Ctlan::PrivateSystem::SceneBase* Ctlan::PublicSystem::SceneManager::GetNowScene()
{
	return m_loadedScene;
}

Ctlan::PrivateSystem::SceneBase* Ctlan::PublicSystem::SceneManager::LoadScene(const char* sceneName)
{
	// 既にシーンがロードされている？
	if (m_scenePool.count(sceneName) > 0)
	{
		m_loadedScene = m_scenePool[sceneName];	// シーンを変更する
		return m_loadedScene;					// シーン情報を返す
	}
	// シーンがロードされていない
	else
	{
		// シーン名と合致するシーンは作成されていない？
		if (!LoadSceneData(sceneName))
		{
			return nullptr;	// nullptrを返す
		}
	}

	return m_loadedScene;	// シーン情報を返す
}
