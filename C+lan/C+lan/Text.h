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

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// �e�L�X�g�Ɋւ��鑀����܂Ƃ߂��N���X	</summary>
		class Text : public PrivateSystem::TextRenderer
		{
			public:
				// ----- functions / �֐� ----- //
				/// <summary>
				///	�R���X�g���N�^	</summary>
				Text() {};
				/// <summary>
				///	�����t���R���X�g���N�^	</summary>
				/// <param name="other">
				/// �l�R�s�[�p�I�u�W�F�N�g	</param>
				Text(const Text* other);

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

				/// <summary>
				///	Text�^�Ƃ̑���I�y���[�^�[	</summary>
				/// <param name="other">
				///	Text�^�̃I�u�W�F�N�g	</param>
				/// <returns>
				///	������Text���	</returns>
				Text& operator=(const Text& other);
		};
	}
}