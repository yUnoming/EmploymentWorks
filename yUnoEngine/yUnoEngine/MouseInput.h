#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Vector2.h"
#include "InputPartsName.h"


namespace PublicSystem
{
	class MouseInput
	{
		public:
			// ----- functions / �֐� ----- //

			/// <summary>
			/// ���݂̃J�[�\�����W���擾����	</summary>
			/// <returns>
			/// ���݂̃J�[�\�����W���h�hVector2�h�h�ŕԂ�	</returns>
			static Vector2 GetCursorPosition();

			/// <summary>
			/// �}�E�X�������ꂽ�u�Ԃ��ǂ������擾����	</summary>
			/// <param name = "_mb">
			/// �^�擾�������}�E�X�̃{�^����	</param>
			/// <returns>
			/// �����ꂽ�u�ԂȂ�""true""�A����ȊO��""false""��Ԃ�	</returns>
			static bool GetMouseDown_Trigger(MouseButtonName _mb);
			/// <summary>
			/// �}�E�X��������Ă��邩�ǂ������擾����	</summary>
			/// <param name = "_mb">
			/// �^�擾�������}�E�X�̃{�^����	</param>
			/// <returns>
			/// ������Ă���Ȃ�""true""�A����ȊO��""false""��Ԃ�	</returns>
			static bool GetMouseDown(MouseButtonName _mb);
			
			/// <summary>
			/// �}�E�X�z�C�[������]����Ă��邩�ǂ������擾����	</summary>
			/// <returns>
			/// ��]����Ă���Ȃ�""true""�A����ȊO��""false""��Ԃ�	</returns>
			static bool GetWheelRotation();

			/// <summary>
			/// �}�E�X�z�C�[�����O����]����Ă��邩�ǂ������擾����	</summary>
			/// <returns>
			/// �O����]����Ă���Ȃ�""true""�A����ȊO��""false""��Ԃ�	</returns>
			static bool GetWheelRotation_Forward();

			/// <summary>
			/// �}�E�X�z�C�[���������]����Ă��邩�ǂ������擾����	</summary>
			/// <returns>
			/// �����]����Ă���Ȃ�""true""�A����ȊO��""false""��Ԃ�	</returns>
			static bool GetWheelRotation_Backward();
	};
}

