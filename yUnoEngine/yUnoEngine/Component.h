#pragma once
#include <list>

// �O���Q��
class GameObject;

class Component
{
	public:
		// ���������� variable ���������� //
		// �I�u�W�F�N�g�̃��X�g��`
		std::list<GameObject*> m_GameObjectList;
		// ���g
		GameObject* Parent = nullptr;

		// ���������� function ���������� //
		// �R���X�g���N�^
		Component() {};
		// �f�X�g���N�^
		virtual ~Component() {};

		// ������
		virtual void Init() {};
		// �I��
		virtual void UnInit() {};
		// �X�V
		virtual void Update() {};
		// �`��
		virtual void Draw() {};
};

