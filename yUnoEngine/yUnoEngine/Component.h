#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <list>


// ������������������������������ //
// �@�@		  �O���Q��  		  //
// ������������������������������ //
class GameObject;


class Component
{
	public:
		// ----- variables / �ϐ� ----- //
		// ���g�̐e�ł���I�u�W�F�N�g
		GameObject* Parent = nullptr;

		// �悭�g����R���|�[�l���g�͌Ăяo����悤�ɂ��Ă���


		// ----- functions / �֐� ----- //
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

