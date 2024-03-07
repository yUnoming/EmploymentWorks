#pragma once
#include "C+lan.h"
#include "Meteor.h"
#include "TemplateCube.h"

class MeteorPool : public EachFunction
{
	private:
		std::list<GameObject*> meteorPool;

	public:
		void Init()
		{
			for (int i = 0; i < 7; i++)
			{
				GameObject* meteor = Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateCube>(1, "Meteor");
				meteor->AddComponent<Meteor>();
				meteorPool.push_back(meteor);
			}
		}

		void Uninit()
		{
			meteorPool.clear();
		}
};

