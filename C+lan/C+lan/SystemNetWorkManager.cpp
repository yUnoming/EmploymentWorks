#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

constexpr unsigned short PORTNO = 49152;

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#pragma comment(lib, "ws2_32.lib")

#include "SystemNetWorkManager.h"

#include <stdio.h>
#include <time.h>
#include <iostream>


Server* Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::m_Server;

void Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::Init()
{
	// �T�[�o�[�̐���
	m_Server = new Server();
}

void Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::Update()
{
	// ���O�C�����Ă����T�[�o�[���V���b�g�_�E�����ꂽ�H
	if (m_Server->IsServerShutdown())
		m_Server->LogoutServer();	// ���O�A�E�g����
}

void Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::Uninit()
{
	// �T�[�o�[�̍폜
	delete m_Server;
}
