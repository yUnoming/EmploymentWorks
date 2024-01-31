#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "Material.h"

#include "ParticlePool.h"
#include "SpectatorCamera.h"
#include "SystemSceneManager.h"

#include <stdlib.h>

class Meteor : public Ctlan::PrivateSystem::GameObject
{
	private:
		Vector3 speed;
		Vector3 addRotation;

		Vector3 startPosition;

		void MeteorInit();

	public:
		Vector3 velocity;
		bool isCalcVelocity = false;
		int lateCount = 0;
		int count = 0;

		/// <summary>
		///	コンストラクタ	</summary>
		Meteor() : GameObject() {};
		/// <summary>
		///	引数付きコンストラクタ	</summary>
		/// <param name="nowScene">
		///	オブジェクトが生成されたシーン	</param>
		Meteor(SceneBase* nowScene) : GameObject(nowScene) {};

		void Init()
		{
			AddComponent<Ctlan::PublicSystem::Material>()->materialColor = Color(0.698f, 0.133f, 0.133f, 1.0f);
			AddComponent<Ctlan::PrivateSystem::ModelRenderer>()->Load("Assets\\Models\\templateCube.obj");
			AddComponent<Ctlan::PublicSystem::BoxCollider>();
			
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
			Meteor* otherMeteor = (Meteor*)other;
			if (otherMeteor)
			{
				otherMeteor->count++;

				if (!isCalcVelocity)
				{
					float e = 0.8f;

					float m1 = 1.0f;
					float vx1 = velocity.x;
					float vy1 = velocity.y;
					// 求めた移動量を代入する変数
					float vx1dash;
					float vy1dash;

					float m2 = 1.0f;
					float vx2 = otherMeteor->velocity.x;
					float vy2 = otherMeteor->velocity.y;
					// 求めた移動量を代入する変数
					float vx2dash;
					float vy2dash;

					vx1dash = ((m1 - e * m2) * vx1 + (1 + e) * m2 * vx2) / (m1 + m2);
					vy1dash = ((m1 - e * m2) * vy1 + (1 + e) * m2 * vy2) / (m1 + m2);
					vx2dash = ((m2 - e * m1) * vx2 + (1 + e) * m1 * vx1) / (m1 + m2);
					vy2dash = ((m2 - e * m1) * vy2 + (1 + e) * m1 * vy1) / (m1 + m2);

					// はねかえり係数
					//float edash = -((v1dash - v2dash) / (v1 - v2));

					// 求めた移動量をセット
					velocity = Vector3(vx1dash, vy1dash, 0.0f);
					otherMeteor->velocity = Vector3(vx2dash, vy2dash, 0.0f);
					isCalcVelocity = true;
					otherMeteor->isCalcVelocity = true;
	
					Vector3 vec = other->transform->position - transform->position;
					Vector3 generatePos = transform->position + (vec * 0.5f);
					Ctlan::PublicSystem::SceneManager::GetNowScene()->GetSceneObject<ParticlePool>("ParticlePool")->GenerateParticle(generatePos);
				}
			}
		}
};

