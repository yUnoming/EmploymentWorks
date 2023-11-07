#pragma once
/**
* @file		FileReader.h
* @brief	FileReader�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.10.29
*/

/// <summary>
/// �e�t�@�C����ǂݍ��ނ��߂̃N���X	</summary>
class FileReader
{
	public:
		// ----- functions / �֐� ----- //
		/// <summary>
		/// ttf�t�@�C����ǂݍ���	</summary>
		/// <param name = "filePath">
		/// �ǂݍ��݂����t�@�C���̎Q�ƃp�X��	</param>
		/// <param name = "fontName">
		/// �t�H���g�̖���	</param>
		static void ReadTtfFile(const wchar_t* filePath, const char* fontName);
};

