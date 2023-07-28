#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>
#include <SimpleMath.h>
#include "Component.h"
#include "Vector3.h"


namespace PublicSystem
{
	class GameObject
	{
	private:
		// ----- variables ----- //
		// �R���|�[�l���g�̃��X�g
		std::list<Component*> m_ComponentList;

	protected:
		// ----- variables ----- //
		// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�\��
		// true: �ʏ퓮�� false: �@�\��~�E��\��
		bool m_Active = true;

		Vector3 m_Position = Vector3(0.0f, 0.0f, 0.0f);	// �ʒu
		Vector3 m_Rotation = Vector3(0.0f, 0.0f, 0.0f);	// ��]
		Vector3 m_Scale = Vector3(1.0f, 1.0f, 1.0f);	// �傫��

	public:
		// ----- methods ----- //
		GameObject() {};
		virtual ~GameObject() {};

		// �I�u�W�F�N�g�P�̂Ɋւ�鏈��
		virtual void Init() {};		// ������
		virtual void UnInit() {};	// �I��
		virtual void Update() {};	// �X�V
		virtual void Draw() {};		// �`��

		// �I�u�W�F�N�g�S�̂Ɋւ�鏈��
		void InitBase();
		void UnInitBase();
		void UpdateBase();
		void DrawBase(DirectX::SimpleMath::Matrix _parentMatrix);

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
}