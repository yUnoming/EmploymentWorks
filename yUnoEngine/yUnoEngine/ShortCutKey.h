#pragma once
/**
* @file		ShortCutKey.h
* @brief	ShortCutKey�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "InputPartsName.h"


/// <summary>
///	�A�v���P�[�V�������x����V�X�e���̈ꕔ	</summary>
namespace yUno_SystemParts
{
	/// <summary>
	///	�V���[�g�J�b�g�L�[�̑���������N���X	</summary>
	class ShortCutKey
	{
		public:
			/// <summary>
			///	���s	</summary>
			static void Run(int keyCommand);
	};
}


