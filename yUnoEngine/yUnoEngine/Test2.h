#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "modelRenderer.h"
#include "BoxCollider.h"
#include "KeyInput.h"
#include "InputPartsName.h"
#include "Material.h"
#include "Text.h"

using namespace PublicSystem;


class Test2 : public GameObject
{
	public:
		void Init()
		{
			//AddComponent<ModelRenderer>()->Load("Assets\\Models\\yUno_TemplateBox.obj");
			//AddComponent<BoxCollider>();
			Material mat;
			AddComponent<Material>();

			transform->position.x = 0.0f;
			transform->position.z = 3.0f;
			Text* textComponent = AddComponent<Text>();
			textComponent->text = "Hello";
			textComponent->fontSize = Vector2(20, 30);

		}

		void Update()
		{
			Text* textComponent = GetComponent<Text>();

			if(KeyInput::GetKeyDownTrigger(P))
			{
				textComponent->text = "bcc";
			}
			else if (KeyInput::GetKeyUpTrigger(P))
			{
				textComponent->text = "Hello";
			}

			if (KeyInput::GetKeyDownTrigger(I))
			{
				textComponent->AddText("World");
			}
		}
};

