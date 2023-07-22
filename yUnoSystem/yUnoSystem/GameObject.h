#pragma once
#include <list>
#include "Component.h"

// �O���Q��
class Component;

class GameObject
{
	public :
		// ���������� variable ���������� //
		// �R���|�[�l���g�̃��X�g
		std::list<Component*> m_ComponentList;

		// ���������� function ���������� //
		// �R���X�g���N�^
		GameObject() {};
		// �f�X�g���N�^
		virtual ~GameObject();

		// �X�V
		void Update();
		// �`��
		void Draw();

		// �R���|�[�l���g�擾
		template<class T>
		T* GetComponent();
		// �R���|�[�l���g�ǉ�
		template<class T>
		T* AddComponent();
		// �R���|�[�l���g�폜
		template<class T>
		T* DeleteComponent();
};
