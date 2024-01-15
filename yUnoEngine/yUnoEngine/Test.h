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
			AddComponent<ModelRenderer>()->Load("Assets/Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();
			AddComponent<Material>()->materialColor = Color(1.0f, 0.0f, 0.0f, 1.0f);

			transform->position.x = 0.0f;
			transform->position.z = 3.0f;
		}
};

