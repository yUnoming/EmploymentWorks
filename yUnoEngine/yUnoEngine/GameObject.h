#pragma once
#include <list>
#include "Component.h"

// �O���Q��
class Component;

class GameObject
{
	public :
		// ----- variables ----- //
		// �R���|�[�l���g�̃��X�g
		std::list<Component*> m_ComponentList;

		// ----- methods ----- //
		GameObject() {};
		virtual ~GameObject();

		virtual void Init();		// ������
		virtual void UnInit();		// �I��
		virtual void Update() {};	// �X�V
		virtual void Draw() {};		// �`��

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
