#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Component.h"
#include "GameObject.h"

class EachFunction : public Component
{
	public:
		// ----- variables / �ϐ� ----- //
		// �������g��\���I�u�W�F�N�g
		GameObject* Myself = nullptr;

		// ���g�̐e�ł���I�u�W�F�N�g
		GameObject* Parent = nullptr;

		// ��{�̃I�u�W�F�N�g���
		class Transform* transform = nullptr;

		// ----- functions / �֐� ----- //
		using Component::Component;
		EachFunction() {};
		//**  �R���|�[�l���g����  **//

		template<class T>
		T* GetComponent()
		{
			return Myself->GetComponent<T>();
		}

		template<class T>
		T* AddComponent()
		{
			return Myself->AddComponent<T>();
		}

		template<class T>
		void DeleteComponent()
		{
			Myself->DeleteComponent<T>();
		}
};