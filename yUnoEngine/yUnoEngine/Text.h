#pragma once
/**
* @file		Text.h
* @brief	Text�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.07
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "TextRenderer.h"
#include <iostream>

namespace PublicSystem
{
	/// <summary>
	/// �e�L�X�g�Ɋւ��鑀����܂Ƃ߂��N���X	</summary>
	class Text : public TextRenderer
	{
		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			///	���݂̃e�L�X�g�ɐV���Ƀe�L�X�g��ǉ�	</summary>
			/// <param name="addText">
			/// �ǉ�����e�L�X�g	</param>
			void AddText(const char* addText);
			/// <summary>
			///	���݂̃e�L�X�g��ύX����	</summary>
			/// <param name="changeText">
			///	�ύX����e�L�X�g	</param>
			void ChangeText(const char* changeText);
			/// <summary>
			///	���݂̃e�L�X�g�̖������폜	</summary>
			void DeleteText();
	};
}

