#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "InputPartsName.h"


using namespace PublicSystem;


class Test2 : public GameObject
{
	public:
		void Init()
		{
			AddComponent<ModelRenderer>()->Load("Assets\\Models\\yUno_TemplateBox.obj");
			AddComponent<BoxCollider>();

			transform->Position.z = 3.5f;
		}
};

