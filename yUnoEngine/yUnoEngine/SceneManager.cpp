#include "SceneManager.h"

std::array<std::list<GameObject*>, 4> PublicSystem::SceneManager::GetSceneObjectAll()
{
	return m_sceneObject;
}
