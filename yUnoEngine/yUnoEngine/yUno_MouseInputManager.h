#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "InputPartsName.h"


namespace yUno_SystemManager
{
	// �}�E�X�̏��
	enum MOUSE_STATE
	{
		NOSTATUS,	// �܂�������Ă��Ȃ� or ���蒴��
		UP,			// �L�[��������Ă���
		DOWN,		// �L�[��������Ă���
	};

	class yUno_MouseInputManager
	{
		public:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			/// ���݂̃}�E�X�̏��
			/// </summary>
			static MOUSE_STATE Now_MouseStatus[3];
			/// <summary>
			/// �O��̃}�E�X�̏��
			/// </summary>
			static MOUSE_STATE Late_MouseStatus[3];

			// ----- functions / �֐� ----- //
			/// <summary>
			/// ���݂̃}�E�X�̏�Ԃ�ۑ����邽�߂̊֐�
			/// </summary>
			static void Keep_Now_MouseStatus();

			/// <summary>
			/// �}�E�X�������ꂽ���Ƃ��Z�b�g����֐�
			/// </summary>
			static void Set_MouseDown(PublicSystem::MouseButtonName _mb);
			/// <summary>
			/// �}�E�X�������ꂽ���Ƃ��Z�b�g����֐�
			/// </summary>
			static void Set_MouseUp(PublicSystem::MouseButtonName _mb);
	};
}

