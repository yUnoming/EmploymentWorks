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
	// ���ɃV�[�������[�h����Ă���H
	if (m_scenePool.count(sceneName) > 0)
	{
		m_loadedScene = m_scenePool[sceneName];	// �V�[����ύX����
		return m_loadedScene;					// �V�[������Ԃ�
	}
	// �V�[�������[�h����Ă��Ȃ�
	else
	{
		// �V�[�����ƍ��v����V�[���͍쐬����Ă��Ȃ��H
		if (!LoadSceneData(sceneName))
		{
			return nullptr;	// nullptr��Ԃ�
		}
	}

	return m_loadedScene;	// �V�[������Ԃ�
}
