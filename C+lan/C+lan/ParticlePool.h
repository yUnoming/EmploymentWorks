#pragma once
#include "GameObject.h"
#include "Particle.h"
#include "SceneManager.h"
#include <list>

class ParticlePool : public Ctlan::PrivateSystem::GameObject
{
	private:
		std::list<Particle*> particlePool;
	
	public:
		void Init()
		{
			for (int i = 0; i < 30; i++)
			{
				Particle* particle = SceneManager::GetNowScene()->AddSceneObject<Particle>(2, "Particle");
				particlePool.push_back(particle);
			}
		}

		void Uninit()
		{
			particlePool.clear();
		}

		void GenerateParticle(Vector3 generatePosition)
		{
			int generateNum = rand() % 3 + 3;
			int generateCount = 0;

			for (Particle* particle : particlePool)
			{
				if (particle->isActive == false)
				{
					particle->ParticleInit();
					particle->transform->position.x = generatePosition.x;
					particle->transform->position.y = generatePosition.y;
					particle->isActive = true;
					generateCount++;
				}

				if (generateNum == generateCount)
					break;
			}

			if (generateCount == 0)
			{
				int a = 0;
				a = a;
			}
		}
};

