#pragma once
#include "GameObject.h"
#include "modelRenderer.h"


class Test : public GameObject
{
	public:
		void Init()
		{
			AddComponent<ModelRenderer>()->Load("Assets\\Models\\box.obj");
			m_Position.z = 3.0f;
			m_Rotation.z = 60.0f;
			m_Rotation.y = 60.0f;
		}
};

