#pragma once
#include "C+lan.h"
#include "Particle.h"

class ParticlePool : public EachFunction
{
	private:
		std::list<GameObject*> particlePool;
	
	public:
		void Init()
		{
			for (int i = 0; i < 30; i++)
			{
				GameObject* particle = SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateCube>(2, "Particle");
				particle->AddComponent<Particle>();
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

			if (particlePool.empty())return;

			for (GameObject* particle : particlePool)
			{
				if (particle->isActive == false)
				{
					particle->GetComponent<Particle>()->ParticleInit();
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

