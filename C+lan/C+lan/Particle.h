#pragma once
#include "C+lan.h"
#include "modelRenderer.h"

class Particle : public EachFunction
{
	private:
		Vector2 weight;
		Vector3 addRotation;
		float elapsedTime = 0.0f;

		Material* mat = nullptr;

	public:

		void Init()
		{
			mat = GetComponent<Material>();
			GetComponent<BoxCollider>()->isActive = false;
			transform->position.z = 5.0f;
			transform->scale *= 0.1f;

			addRotation.x = (rand() % 11) * 0.5f;
			addRotation.y = (rand() % 11) * 0.5f;
			addRotation.z = (rand() % 11) * 0.5f;

			ParticleInit();
			gameObject->isActive = false;
		}

		void Update()
		{
			float InitialSpeed = 0.00147f * 5;	// 初速度
			float GravitySpeed = 0.0098f;		// 重力加速度
			float x = InitialSpeed * weight.x * 0.7f;
			float y = InitialSpeed * weight.y;
			y = (y * elapsedTime - 0.5f * GravitySpeed * (elapsedTime * elapsedTime));

			transform->position.x += x;
			transform->position.y += y;

			transform->rotation += addRotation;

			elapsedTime += Time::DeltaTime * 0.001f;

			if (elapsedTime > 2.0f)
				gameObject->isActive = false;
			else
				mat->materialColor.a = (2.0f - elapsedTime) / 2.0f;
			 
		}

		void ParticleInit()
		{
			float angle = (rand() % 360) * 360.0f / 180.0f;
			weight.x = cos(angle);
			weight.y = sin(angle);

			elapsedTime = 0.0f;

			mat->materialColor = Color(0.29f, 0.368f, 0.467f, 1.0f);
		}
};

