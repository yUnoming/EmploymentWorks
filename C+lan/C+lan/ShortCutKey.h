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


namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	�A�v���P�[�V�������x����V�X�e��	</summary>
		namespace ApplicationSystem
		{
			/// <summary>
			///	�V���[�g�J�b�g�L�[�̑���������N���X	</summary>
			class ShortCutKey
			{
				public:
					/// <summary>
					///	���s	</summary>
					/// <param name="keyCommand">
					///	�L�[�̒l	</param>
					static void Run(int keyCommand);
			};
		}
	}
}