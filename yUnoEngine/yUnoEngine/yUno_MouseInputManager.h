#pragma once
/**
* @file		yUno_MouseInputManager.h
* @brief	yUno_MouseInputManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.07
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "InputPartsName.h"


namespace yUno_SystemManager
{
	/// <summary>
	///	�}�E�X���͂𔻒肷�邽�߂̏������Ǘ�����N���X	</summary>
	class yUno_MouseInputManager
	{
		private:
			/// <summary>
			///	�}�E�X�̏��	</summary>
			enum MouseStatus
			{
				/// <summary>
				///	�܂�������Ă��Ȃ��^���蒴��	</summary>
				NoStatus,
				/// <summary>
				/// ������Ă���		</summary>
				Up,
				/// <summary>
				///	������Ă���	</summary>
				Down
			};
			/// <summary>
			///	�}�E�X�z�C�[���̏��	</summary>
			enum MouseWheelStatus
			{
				ForwardRotation,	// �O����]
				BackwardRotation,	// �����]
				NotRotation			// ��]���Ă��Ȃ�
			};

			// ----- variables / �ϐ� ----- //
			/// <summary>
			///	���݂̃}�E�X�̏��	</summary>
			static MouseStatus m_nowMouseState[3];
			/// <summary>
			/// �O��̃}�E�X�̏��	</summary>
			static MouseStatus m_lateMouseState[3];	
			/// <summary>
			/// �}�E�X�z�C�[���̓��͒l
			/// ���̒l�F�O���ɉ�]
			/// ���̒l�F����ɉ�]	</summary>
			static MouseWheelStatus m_mouseWheelState;

		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			/// ���݂̃}�E�X�̏�Ԃ�ۑ�	</summary>
			static void KeepNowMouseState();
			/// <summary>
			/// �}�E�X�������ꂽ���Ƃ��Z�b�g	</summary>
			/// <param name = "button">
			/// �����ꂽ�}�E�X�̃{�^����	</param>
			static void SetMouseDown(PublicSystem::MouseButtonName button);
			/// <summary>
			/// �}�E�X�������ꂽ���Ƃ��Z�b�g
			/// </summary>
			/// <param name = "button">
			/// �����ꂽ�}�E�X�̃{�^����</param>
			static void SetMouseUp(PublicSystem::MouseButtonName button);
			/// <summary>
			/// �}�E�X�z�C�[���̏�Ԃ��Z�b�g	</summary>
			/// <param name="mouseWheelParam">
			/// �}�E�X�z�C�[���̓��͒l	</param>
			static void SetMouseWheelState(int mouseWheelParam);

			/// <summary>
			/// �}�E�X�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
			/// <param name = "button">
			/// ���肷��}�E�X�̃{�^����	</param>
			/// <returns>
			/// �����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
			static bool GetMouseDownTrigger(PublicSystem::MouseButtonName button);
			/// <summary>
			/// �}�E�X��������Ă��邩�ǂ����𔻒�	</summary>
			/// <param name = "button">
			/// ���肷��}�E�X�̃{�^����	</param>
			/// <returns>
			/// ������Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
			static bool GetMouseDown(PublicSystem::MouseButtonName button);

			/// <summary>
			///	�}�E�X�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
			/// <param name="button">
			///	���肷��}�E�X�̃{�^����	</param>
			/// <returns>
			///	�����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
			static bool GetMouseUpTrigger(PublicSystem::MouseButtonName button);
			/// <summary>
			///	�}�E�X��������Ă��邩�ǂ����𔻒�	</summary>
			/// <param name="button">
			///	���肷��}�E�X�̃{�^����	</param>
			/// <returns>
			///	������Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
			static bool GetMouseUp(PublicSystem::MouseButtonName button);

			/// <summary>
			/// �}�E�X�z�C�[������]����Ă��邩�ǂ����𔻒�	</summary>
			/// <returns>
			/// ��]����Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
			static bool GetWheelRotation();
			/// <summary>
			/// �}�E�X�z�C�[�����O����]����Ă��邩�ǂ����𔻒�	</summary>
			/// <returns>
			/// �O����]����Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
			static bool GetWheelRotationForward();
			/// <summary>
			/// �}�E�X�z�C�[���������]����Ă��邩�ǂ����𔻒�	</summary>
			/// <returns>
			/// �����]����Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
			static bool GetWheelRotationBackward();

	};
}

