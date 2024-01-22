#pragma once
/**
* @file		MouseInput.h
* @brief	MouseInput�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.05
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Vector2.h"
#include "InputPartsName.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	�}�E�X���͂𔻒肷�邽�߂̋@�\���܂Ƃ߂��N���X	</summary>
		class MouseInput
		{
			public:
				// ----- functions / �֐� ----- //
				/// <summary>
				/// ���݂̃J�[�\�����W���擾	</summary>
				/// <returns>
				/// ���݂̃J�[�\�����W	</returns>
				static Vector2 GetCursorPosition();

				/// <summary>
				/// �}�E�X�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
				/// <param name = "button">
				/// ���肷��}�E�X�̃{�^����	</param>
				/// <returns>
				/// �����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
				static bool GetMouseDownTrigger(MouseButtonName button);
				/// <summary>
				/// �}�E�X��������Ă��邩�ǂ����𔻒�	</summary>
				/// <param name = "button">
				/// ���肷��}�E�X�̃{�^����	</param>
				/// <returns>
				/// ������Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
				static bool GetMouseDown(MouseButtonName button);

				/// <summary>
				///	�}�E�X�������ꂽ�u�Ԃ��ǂ����𔻒�	</summary>
				/// <param name="button">
				///	���肷��}�E�X�̃{�^����	</param>
				/// <returns>
				///	�����ꂽ�u�ԂȂ�true�A����ȊO�Ȃ�false	</returns>
				static bool GetMouseUpTrigger(MouseButtonName button);
				/// <summary>
				///	�}�E�X��������Ă��邩�ǂ����𔻒�	</summary>
				/// <param name="button">
				///	���肷��}�E�X�̃{�^����	</param>
				/// <returns>
				///	������Ă���Ȃ�true�A����ȊO�Ȃ�false	</returns>
				static bool GetMouseUp(MouseButtonName button);

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