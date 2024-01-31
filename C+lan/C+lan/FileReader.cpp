// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "FileReader.h"
#include "SystemTextRendererManager.h"
#include <Shlwapi.h>
#include <iostream>
#include <tchar.h>


// ������������������������������ //
// �@�@		�Q�l���\�[�X	 �@�@ //
// ������������������������������ //
// ReadTtfFile���t�H���g�̐����A�쐬
// https://hakase0274.hatenablog.com/entry/2018/11/17/170918


void FileReader::ReadTtfFile(const wchar_t* filePath, const char* fontName)
{
	// �o�b�t�@�T�C�Y�̎擾
	int bufferSize = MultiByteToWideChar(CP_UTF8, 0, fontName, -1, nullptr, 0);
	// �o�b�t�@�̊m��
	WCHAR* wideFontName = new WCHAR[bufferSize];
	// �}���`�o�C�g�����񂩂烏�C�h������ɕϊ�
	MultiByteToWideChar(CP_UTF8, 0, fontName, -1, wideFontName, bufferSize);

	// �V�X�e���Ƀt�H���g���\�[�X��ǉ�����
	// �ǉ����ꂽ�t�H���g�̐����擾���Ă���
	int fontNum = AddFontResourceExW(
		filePath,				// �ǉ��������t�H���g�̎Q�ƃp�X
		FR_PRIVATE,				// �ǉ�����t�H���g�̓���
		0						// 0�w���OK
	);

	// �t�H���g���ǉ�����Ȃ������H
	if (fontNum == 0)
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
		*wideFontName					// �t�H���g�̃^�C�v�t�F�C�X��
	};

	// �t�H���g�̍쐬
	HFONT hFont = CreateFontIndirect(&lf);

	// �t�H���g���쐬�o���Ȃ������H
	if (hFont == NULL)
	{
		std::cout << "Error!!! ErrorCode�F" << GetLastError() << std::endl;
	}

	// �쐬�����t�H���g��ǉ�����
	SystemManager::SystemTextRendererManager::SetFont(hFont);
	// �폜
	delete[] wideFontName;
}
