#pragma once
/**
* @file		SystemMouseInputManager.h
* @brief	SystemMouseInputManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.07
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "InputPartsName.h"
#include "Vector2.h"

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	�}�E�X���͂𔻒肷�邽�߂̏������Ǘ�����N���X	</summary>
			class SystemMouseInputManager
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

					/// <summary>
					///	�O��̃J�[�\�����W	</summary>
					static PublicSystem::Vector2 m_lateCursorPosition;
					/// <summary>
					///	���݂̃J�[�\�����W	</summary>
					static PublicSystem::Vector2 m_nowCursorPosition;

				public:
					// ----- functions / �֐� ----- //
					/// <summary>
					///	�X�V����	</summary>
					static void Update();

					/// <summary>
					///	�O��̃J�[�\�����W���擾	</summary>
					/// <returns>
					///	�O��̃J�[�\�����W	</returns>
					static PublicSystem::Vector2 GetLateCursorPosition() { return m_lateCursorPosition; };
					/// <summary>
					/// ���݂̃J�[�\�����W���擾	</summary>
					/// <returns>
					///	���݂̃J�[�\�����W	</returns>
					static PublicSystem::Vector2 GetNowCursorPosition() { return m_nowCursorPosition; };

					/// <summary>
					/// ���݂̃}�E�X�̏�Ԃ�ۑ�	</summary>
					static void KeepNowMouseState();
					/// <summary>
					/// �}�E�X�������ꂽ���Ƃ��Z�b�g	</summary>
					/// <param name = "button">
					/// �����ꂽ�}�E�X�̃{�^����	</param>
					static void SetMouseDown(Ctlan::PublicSystem::MouseButtonName button);
					/// <summary>
					/// �}�E�X�������ꂽ���Ƃ��Z�b�g
					/// </summary>
					/// <param name = "button">
					/// �����ꂽ�}�E�X�̃{�^����</param>
					static void SetMouseUp(Ctlan::PublicSystem::MouseButtonName button);
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
					static bool GetMouseDownTrigger(Ctlan::PublicSystem::MouseButtonName button);
					/// <summary>
					/// �}�E�X��������Ă��邩�ǂ����𔻒�	</summary>
					/// <param name = "button">
					/// ���肷��}�E�X�̃{�^����	</param>
					/// <returns>
					/// ������Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
					static bool GetMouseDown(Ctlan::PublicSystem::MouseButtonName button);

					/// <summary>
					///	�}�E�X�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
					/// <param name="button">
					///	���肷��}�E�X�̃{�^����	</param>
					/// <returns>
					///	�����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
					static bool GetMouseUpTrigger(Ctlan::PublicSystem::MouseButtonName button);
					/// <summary>
					///	�}�E�X��������Ă��邩�ǂ����𔻒�	</summary>
					/// <param name="button">
					///	���肷��}�E�X�̃{�^����	</param>
					/// <returns>
					///	������Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
					static bool GetMouseUp(Ctlan::PublicSystem::MouseButtonName button);

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
	}
}

