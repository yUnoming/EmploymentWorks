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

			// ���݂̃J�[�\�����W��Ԃ��֐�
			static Vector2 GetCursorPosition();

			// �}�E�X�������ꂽ�u�Ԃ����ǂ�����Ԃ��֐�
			static bool GetMouseDown_Trigger(MouseButtonName _mb);
			// �}�E�X��������Ă��邩�ǂ�����Ԃ��֐�
			static bool GetMouseDown(MouseButtonName _mb);
	};
}

