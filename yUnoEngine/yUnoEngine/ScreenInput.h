#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Vector2.h"


namespace PublicSystem
{
	// ��ʓ��͂Ɋւ��鏈�����܂Ƃ߂��N���X
	class ScreenInput
	{
		public:
			// ----- functions / �֐� ----- //

			// �w�肵�����W���X�N���[�����W�ɕϊ����ĕԂ��֐�
			static Vector2 GetScreenPosition(Vector2 _paramPosition);
	};
}

