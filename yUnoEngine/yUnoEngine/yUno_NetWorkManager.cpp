#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

constexpr unsigned short PORTNO = 49152;

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#pragma comment(lib, "ws2_32.lib")

#include "yUno_NetWorkManager.h"

#include <stdio.h>
#include <time.h>
#include <iostream>


Server* yUno_SystemManager::yUno_NetWorkManager::m_Server;

void yUno_SystemManager::yUno_NetWorkManager::Init()
{
	// �T�[�o�[�̐���
	m_Server = new Server();
}

void yUno_SystemManager::yUno_NetWorkManager::UnInit()
{
	// �T�[�o�[�̍폜
	delete m_Server;
}
