#pragma once
#include "GameObject.h"
#include "Meteor.h"

class MeteorPool : public Ctlan::PrivateSystem::GameObject
{
	private:
		std::list<Meteor*> MeteorPool;

	public:
		void Init()
		{
			for (int i = 0; i < 7; i++)
			{
				Meteor* meteor = Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Meteor>(1, "Meteor");
				MeteorPool.push_back(meteor);
			}
		}

		void Uninit()
		{
			MeteorPool.clear();
		}
};

