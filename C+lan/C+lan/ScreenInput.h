#pragma once
/**
* @file		ScreenInput.h
* @brief	ScreenInput�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Vector2.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// // ��ʓ��͂Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
		class ScreenInput
		{
		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			///	�w�肵�����W���X�N���[�����W�ɕϊ����ĕԂ��֐�	</summary>
			/// <param name="paramPosition">
			///	�ϊ����������W	</param>
			/// <returns>
			/// �ϊ������X�N���[�����W </returns>
			static Vector2 GetScreenPosition(Vector2 paramPosition);
		};
	}
}