#include "Meteor.h"
#include "SceneManager.h"

void Meteor::MeteorInit()
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
