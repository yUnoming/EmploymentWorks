#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"


class Test : public GameObject
{
	public:
		void Init()
		{
			AddComponent<ModelRenderer>()->Load("Assets\\Models\\box.obj");

			transform->Position.z = 3.0f;
			transform->Rotation.z = 60.0f;
			transform->Rotation.y = 60.0f;
		}
};

