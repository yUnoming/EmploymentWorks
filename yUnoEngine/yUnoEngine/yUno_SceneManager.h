#pragma once
#include <list>
#include <array>
#include "GameObject.h"

class yUno_SceneManager
{
	protected:
		// �V�[�����̃I�u�W�F�N�g
		std::array<std::list<GameObject*>, 4> m_SceneObject;

	public:
		// ----- methods ----- //
		yUno_SceneManager() {};
		virtual ~yUno_SceneManager() {};

		// �V�[���P�̂Ɋւ�鏈��
		virtual void Init() {};		// ������
		virtual void UnInit() {};	// �I��
		virtual void Update() {};	// �X�V
		virtual void Draw() {};		// �`��

		// �V�[���S�ʂɊւ�鏈��
		void InitBase();	// ������
		void UnInitBase();	// �I��
		void UpdateBase();	// �X�V
		void DrawBase();	// �`��
};

