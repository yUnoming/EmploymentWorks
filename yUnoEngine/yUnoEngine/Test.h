#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "Material.h"


using namespace PublicSystem;


class Test : public GameObject
{
	public:
		void Init()
		{
			AddComponent<ModelRenderer>()->Load("Assets\\Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();
			AddComponent<Material>();

			transform->Position.x = 0.0f;
			transform->Position.z = 3.0f;
		}

		void Update()
		{
			if (KeyInput::GetKeyDown_Trigger(Enter))
			{
				printf("X : %f, Y : %f, Z : %f", transform->Position.x, transform->Position.y, transform->Position.z);
			}
		}
};

