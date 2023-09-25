#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "InputPartsName.h"


namespace yUno_SystemManager
{
	// �}�E�X�̏��
	enum MOUSE_STATUS
	{
		NOSTATUS,	// �܂�������Ă��Ȃ� or ���蒴��
		UP,			// �L�[��������Ă���
		DOWN,		// �L�[��������Ă���
	};

	// �}�E�X�z�C�[���̏��
	enum MOUSEWHEEL_STATUS
	{
		FORWARD_ROTATION,	// �O����]
		BACKWARD_ROTATION,	// �����]
		NOT_ROTATION,		// ��]���Ă��Ȃ�
	};

	class yUno_MouseInputManager
	{
		public:
			// ----- variables / �ϐ� ----- //

			// ���݂̃}�E�X�̏��
			static MOUSE_STATUS Now_Mouse_Status[3];

			// �O��̃}�E�X�̏��
			static MOUSE_STATUS Late_Mouse_Status[3];

			// �}�E�X�z�C�[���̓��͒l
			// ���̒l�F�O���ɉ�]
			// ���̒l�F����ɉ�]
			static MOUSEWHEEL_STATUS MouseWheel_Status;

			// ----- functions / �֐� ----- //
			/// <summary>
			/// ���݂̃}�E�X�̏�Ԃ�ۑ�����
			/// </summary>
			static void Keep_Now_MouseStatus();
			/// <summary>
			/// �}�E�X�������ꂽ���Ƃ��Z�b�g����
			/// </summary>
			/// <param name = "_mb">�^�Z�b�g�������}�E�X�̃{�^����</param>
			static void Set_MouseDown(PublicSystem::MouseButtonName _mb);
			/// <summary>
			/// �}�E�X�������ꂽ���Ƃ��Z�b�g����֐�
			/// </summary>
			/// <param name = "_mb">�^�Z�b�g�������}�E�X�̃{�^����</param>
			static void Set_MouseUp(PublicSystem::MouseButtonName _mb);
			/// <summary>
			/// �}�E�X�z�C�[���̓��͒l���Z�b�g����
			/// </summary>
			static void Set_MouseWheel_Status(int _wheelParam);

	};
}

