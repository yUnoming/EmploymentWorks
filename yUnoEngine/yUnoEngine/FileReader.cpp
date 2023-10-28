// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "FileReader.h"
#include "yUno_TextRendererManager.h"
#include <Shlwapi.h>
#include <iostream>
#include <tchar.h>


void FileReader::Read_ttfFile(const wchar_t* _filePath, const char* _fontName)
{
	// �V�X�e���Ƀt�H���g���\�[�X��ǉ�����
	// �ǉ����ꂽ�t�H���g�̐����擾���Ă���
	int Font_Num = AddFontResourceEx(
		_filePath,				// �ǉ��������t�H���g�̎Q�ƃp�X
		FR_PRIVATE,				// �ǉ�����t�H���g�̓���
		0						// 0�w���OK
	);

	// �t�H���g���ǉ�����Ȃ������H
	if (Font_Num == 0)
	{
		std::cout << "Error!!! ErrorCode�F" << GetLastError() << std::endl;
	}


	// �t�H���g�̐���
	LOGFONT lf = {
		1000,							// �t�H���g�̍���
		0,								// �t�H���g�̕�
		0,								// �E���x�N�g���ƃf�o�C�X��X���̊Ԃ̊p�x
		0,								// �����̊�{���ƃf�o�C�X��X���̊Ԃ̊p�x
		1,								// �t�H���g�̑���
		FALSE,							// TRUE�Ȃ�Α̃t�H���g�ɂȂ�
		FALSE,							// TRUE�Ȃ牺���t���t�H���g�ɂȂ�
		FALSE,							// TRUE�Ȃ���������t�H���g�ɂȂ�
		DEFAULT_CHARSET,				// �����Z�b�g
		OUT_DEFAULT_PRECIS,				// �o�͐��x
		CLIP_DEFAULT_PRECIS,			// �N���b�s���O�̐��x
		PROOF_QUALITY,					// �o�͕i��
		DEFAULT_PITCH | FF_DONTCARE,	// �t�H���g�̃s�b�`�ƃt�@�~��
		*_fontName						// �t�H���g�̃^�C�v�t�F�C�X��
	};

	// �t�H���g�̍쐬
	HFONT hFont = CreateFontIndirect(&lf);

	// �t�H���g���쐬�o���Ȃ������H
	if (hFont == NULL)
	{
		std::cout << "Error!!! ErrorCode�F" << GetLastError() << std::endl;
	}

	// �쐬�����t�H���g��ǉ�����
	yUno_SystemManager::yUno_TextRendererManager::Set_Font(hFont);
}
