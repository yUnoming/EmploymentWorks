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


	// IP�A�h���X�\��
	{
		char hostname[256];
		gethostname(hostname, 256);

		LPHOSTENT lphe;

		lphe = gethostbyname(hostname);
		if (lphe == nullptr)
		{
			printf("gethostbuname error!!\n");
		}
		else
		{
			in_addr ipadr{};
			memcpy(&ipadr.S_un.S_addr, lphe->h_addr_list[0], 4);
			printf("ipaddress : %s \n", inet_ntoa(ipadr));
		}
	}

	// �\�P�b�g����
	m_mySocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_mySocket == INVALID_SOCKET)
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
	sts = bind(m_mySocket, (sockaddr*)&myAddress, sizeof(sockaddr));
	if (sts == SOCKET_ERROR)
	{
		std::cout << "�\�P�b�g�ւ̊��蓖�ĂɎ��s���܂���" << std::endl;
		return 0;
	}

	// ��M�X���b�h����
	m_receiveThread = std::thread(&yUno_SystemManager::yUno_NetWorkManager::ReceiveThread, this);

	// �ʐM���s���Ă��邱�Ƃ�ۑ�
	isCommunication = true;

	std::cout << "NetWork Communication Start" << std::endl;
}

int yUno_SystemManager::yUno_NetWorkManager::End()
{
	// �ʐM���s���Ă���H
	if (isCommunication)
	{
		//�@�\�P�b�g���N���[�Y���A�G���[�����������H
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode�F" << errorCode << std::endl;
		}
		// ��M�҂���Ԃ���������
		isReceiveWaiting = false;
		
		// �X���b�h�̏I����҂�
		m_receiveThread.join();

		// WINSOCK�̏I������
		WSACleanup();

		isCommunication = false;

		std::cout << "NetWork Communication End" << std::endl;
	}
	return 0;
}

void yUno_SystemManager::yUno_NetWorkManager::ReceiveThread()
{
	int			errcode;	// �v�h�m�r�n�b�j�̃G���[�R�[�h
	sockaddr_in fromaddr{};	// ���M���A�h���X
	int fromAddrLength = 0;	// ���M���A�h���X���Z�b�g�����ϐ��̒���
	// ��M�҂���Ԃɂ���
	isReceiveWaiting = true;

	while (true)
	{
		fromAddrLength = sizeof(sockaddr);

		memset(m_receiveBuffer, 0, sizeof(m_receiveBuffer));

		int sts = recvfrom(
			m_mySocket,
			(char*)m_receiveBuffer,
			sizeof(m_receiveBuffer),
			0,
			(sockaddr*)&fromaddr,
			&fromAddrLength);

		if (sts != SOCKET_ERROR)
		{
			printf("��M�f�[�^ : %s \n", m_receiveBuffer);
			printf("���M���h�o�A�h���X/�|�[�g�ԍ� %s/%d \n",
				inet_ntoa(fromaddr.sin_addr),
				ntohs(fromaddr.sin_port));

			// ��M�f�[�^���M���O
			//loggingdata(m_receiveBuffer, fromaddr);

			int len = static_cast<int>(strlen(m_sendBuffer));	// ���M�����񒷂��擾
			sts = sendto(
				m_mySocket,				// �\�P�b�g�ԍ�
				m_sendBuffer,			// ���M�f�[�^
				len,					// ���M�f�[�^��
				0,						// �t���O
				(sockaddr*)&fromaddr,	// ���M��A�h���X
				sizeof(sockaddr));		// �A�h���X�\���̂̃o�C�g�T�C�Y
			//if (sts == SOCKET_ERROR)
			//{
			//	errcode = WSAGetLastError();
			//	std::cout << "ErrorCode�F" << errcode << std::endl;
			//	break;
			//}
		}
		// ��M�҂���Ԃ��������ꂽ�H
		else if(!isReceiveWaiting)
		{
			errcode = WSAGetLastError();
			std::cout << "RecieveThread() Failed!!! ErrorCode�F" << errcode << std::endl;
			break;
		}
	}
	return;
}
