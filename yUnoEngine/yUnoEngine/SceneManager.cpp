#include "SceneManager.h"

std::array<std::list<GameObject*>, 4> PublicSystem::SceneManager::GetSceneObjectAll()
{
	return m_loadedScene->GetAllSceneObjects();
}
SceneBase* PublicSystem::SceneManager::GetNowScene()
{
	return m_loadedScene;
}

SceneBase* PublicSystem::SceneManager::LoadScene(const char* sceneName)
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
