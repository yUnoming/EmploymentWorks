#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

constexpr unsigned short PORTNO = 49152;

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#pragma comment(lib, "ws2_32.lib")

#include "yUno_NetWorkManager.h"

#include <winsock2.h>
#include <stdio.h>
#include <time.h>
#include <thread>
#include <iostream>

int yUno_SystemManager::yUno_NetWorkManager::Start()
{
	WSADATA wsa;	// WinSock�̏������f�[�^���i�[
	WORD	verNo;	// �o�[�W�����w��
	int sts;		// WinSock�����������������ꂽ�����

	// �o�[�W����2.2��v��
	verNo = MAKEWORD(2, 2);

	// WinSock���������A�G���[�����������H
	if (WSAStartup(
		verNo,	// �v���o�[�W����
		&wsa)	// WinSock�f�[�^���i�[���邽�߂̕ϐ�
		== SOCKET_ERROR)
	{
		int errorCode = WSAGetLastError();
		std::cout << "WSAStartup() Failed!!! ErrorCode�F" << errorCode << std::endl;
		return 0;
	}

	// �v�������o�[�W�����𗘗p�ł��邩�m�F����
	if (verNo != wsa.wVersion)
	{
		std::cout << "�v�������o�[�W�����͗��p�ł��܂���" << std::endl;
		return 0;
	}

	// �\�P�b�g����
	SOCKET mySocket;		// �\�P�b�g
	mySocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mySocket == INVALID_SOCKET)
	{
		std::cout << "�\�P�b�g�̐����Ɏ��s���܂���" << std::endl;
		return 0;
	}

	// ���g�̃A�h���X��ݒ�
	sockaddr_in myAddress{};	// ���g�̃A�h���X
	myAddress.sin_port = htons(PORTNO);
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// �����̃\�P�b�g��IP�A�h���X�A�|�[�g�ԍ������蓖�Ă�
	sts = bind(mySocket, (sockaddr*)&myAddress, sizeof(sockaddr));
	if (sts == SOCKET_ERROR)
	{
		std::cout << "�\�P�b�g�ւ̊��蓖�ĂɎ��s���܂���" << std::endl;
		return 0;
	}

}

int yUno_SystemManager::yUno_NetWorkManager::End()
{
	//�@�\�P�b�g���N���[�Y���A�G���[�����������H
	//if (closesocket(mysocket) != 0)
	//{
	//	int errorCode = WSAGetLastError();
	//	std::cout << "closesocket() Failed ErrorCode�F" << errorCode << std::endl;
	//	return 0;
	//}

	// WINSOCK�̏I������
	WSACleanup();
	return 0;
}
