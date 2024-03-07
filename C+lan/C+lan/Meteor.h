#pragma once
#include "C+lan.h"
#include "modelRenderer.h"
#include "ParticlePool.h"

class Meteor : public EachFunction
{
	private:
		Vector3 speed;
		Vector3 addRotation;

		Vector3 startPosition;

		void MeteorInit()
		{
			int pattern = rand() % 4;
			switch (pattern)
			{
			case 0:
				transform->position.x = 16.0f;
				transform->position.y = (rand() % 1801 - 900) * 0.01f;
				break;
			case 1:
				transform->position.x = -16.0f;
				transform->position.y = (rand() % 1801 - 900) * 0.01f;
				break;
			case 2:
				transform->position.x = (rand() % 3201 - 1600) * 0.01f;
				transform->position.y = 9.0f;
				break;
			case 3:
				transform->position.x = (rand() % 3201 - 1600) * 0.01f;
				transform->position.y = -9.0f;
				break;
			}

			GameObject* mainCamera = SceneManager::GetNowScene()->GetSceneObject("MainCamera");

			speed = mainCamera->transform->position - transform->position;
			speed *= (rand() % 100 + 1) * 0.03f;
			speed.z = 0.f;
			velocity = speed * 0.001f;

			transform->rotation += addRotation;
		}

	public:
		Vector3 velocity;
		bool isCalcVelocity = false;
		int lateCount = 0;
		int count = 0;

		void Init()
		{
			GetComponent<Ctlan::PublicSystem::Material>()->materialColor = Color(0.698f, 0.133f, 0.133f, 1.0f);
			
			transform->position.z = 8.5f;
			transform->scale *= 0.7f;

			addRotation.x = (rand() % 11) * 0.1f;
			addRotation.y = (rand() % 11) * 0.1f;
			addRotation.z = (rand() % 11) * 0.1f;

			MeteorInit();
			startPosition = transform->position;
		}

		void Update()
		{
			transform->position += velocity;
			transform->rotation += addRotation;

			float length = sqrtf(powf(transform->position.x - startPosition.x, 2.f) + powf(transform->position.y - startPosition.y, 2.f));
			if (abs(length) > 25.f)
				MeteorInit();

			if(count == lateCount)
				isCalcVelocity = false;

			lateCount = count;
		}

		void HitCollision(GameObject* other)
		{
			count++;
			if (other->GetComponent<Meteor>())
			{
				Meteor* otherMeteor = other->GetComponent<Meteor>();
				otherMeteor->count++;

				if (!isCalcVelocity)
				{
					float e = 0.8f;
	
					float m1 = 1.0f;
					float vx1 = velocity.x;
					float vy1 = velocity.y;
					// ‹‚ß‚½ˆÚ“®—Ê‚ð‘ã“ü‚·‚é•Ï”
					float vx1dash;
					float vy1dash;

					float m2 = 1.0f;
					float vx2 = otherMeteor->velocity.x;
					float vy2 = otherMeteor->velocity.y;
					// ‹‚ß‚½ˆÚ“®—Ê‚ð‘ã“ü‚·‚é•Ï”
					float vx2dash;
					float vy2dash;

					vx1dash = ((m1 - e * m2) * vx1 + (1 + e) * m2 * vx2) / (m1 + m2);
					vy1dash = ((m1 - e * m2) * vy1 + (1 + e) * m2 * vy2) / (m1 + m2);
					vx2dash = ((m2 - e * m1) * vx2 + (1 + e) * m1 * vx1) / (m1 + m2);
					vy2dash = ((m2 - e * m1) * vy2 + (1 + e) * m1 * vy1) / (m1 + m2);

					// ‚Í‚Ë‚©‚¦‚èŒW”
					//float edash = -((v1dash - v2dash) / (v1 - v2));

					// ‹‚ß‚½ˆÚ“®—Ê‚ðƒZƒbƒg
					velocity = Vector3(vx1dash, vy1dash, 0.0f);
					otherMeteor->velocity = Vector3(vx2dash, vy2dash, 0.0f);
					isCalcVelocity = true;
					otherMeteor->isCalcVelocity = true;
	
					Vector3 vec = other->transform->position - transform->position;
					Vector3 generatePos = transform->position + (vec * 0.5f);

					GameObject* particlePool = Ctlan::PublicSystem::SceneManager::GetNowScene()->GetSceneObject("ParticlePool");
					particlePool->GetComponent<ParticlePool>()->GenerateParticle(generatePos);
				}
			}
		}
};

