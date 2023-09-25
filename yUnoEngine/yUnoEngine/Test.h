#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"


using namespace PublicSystem;


class Test : public GameObject
{
	public:
		void Init()
		{
			AddComponent<ModelRenderer>()->Load("Assets\\Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();

			transform->Position.x = 0.0f;
			transform->Position.z = 3.0f;
			//transform->Rotation.z = 60.0f;
			//transform->Rotation.y = 60.0f;
		}

		void Update()
		{
			if (KeyInput::GetKeyDown(W))
				transform->Position.z += 0.01f;
			if (KeyInput::GetKeyDown(A))
				transform->Position.x -= 0.01f;
			if (KeyInput::GetKeyDown(S))
				transform->Position.z -= 0.01f;
			if (KeyInput::GetKeyDown(D))
				transform->Position.x += 0.01f;

			if (KeyInput::GetKeyDown_Trigger(Enter))
			{
				printf("X : %f, Y : %f, Z : %f", transform->Position.x, transform->Position.y, transform->Position.z);
			}
		}
};

