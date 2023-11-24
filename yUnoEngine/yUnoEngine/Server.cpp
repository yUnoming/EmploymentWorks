// ������������������������������ //
// �@�@		 �}�N����`	     	  //
// ������������������������������ //
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

constexpr unsigned short PORTNO = 49152;

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#pragma comment(lib, "ws2_32.lib")

#include "yUno_NetWorkManager.h"
#include "Server.h"
#include "SceneManager.h"
#include "Test.h"

#include <stdio.h>
#include <time.h>
#include <iostream>

char g_rockObject[256]{};

void Server::ReceiveThread()
{
	int			errcode;		// �v�h�m�r�n�b�j�̃G���[�R�[�h
	int myAddressLength = 0;	// ���M���A�h���X���Z�b�g�����ϐ��̒���

	while (true)
	{
		myAddressLength = sizeof(sockaddr);

		memset(m_messageData.receiveMessage, 0, sizeof(m_messageData.receiveMessage));

		int sts = recvfrom(
			m_mySocket,
			(char*)m_messageData.receiveMessage,
			sizeof(m_messageData.receiveMessage),
			0,
			(sockaddr*)&m_sendAddress,
			&myAddressLength);

		if (sts != SOCKET_ERROR)
		{
			if (strcmp(m_messageData.receiveMessage, "LoginSuccess") == 0)
			{
				std::cout << "Login Server" << std::endl;
			}
			else if (strcmp(m_messageData.receiveMessage, "ServerLogin") == 0)
			{
				printf("��M�f�[�^ : %s \n", m_messageData.receiveMessage);
				printf("���M���h�o�A�h���X/�|�[�g�ԍ� %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));

				strcpy_s(m_messageData.sendMessage, sizeof(m_messageData.sendMessage), "LoginSuccess");
				int len = static_cast<int>(strlen(m_messageData.sendMessage));	// ���M�����񒷂��擾
				sts = sendto(
					m_mySocket,					// �\�P�b�g�ԍ�
					m_messageData.sendMessage,	// ���M�f�[�^
					len,						// ���M�f�[�^��
					0,							// �t���O
					(sockaddr*)&m_sendAddress,	// ���M��A�h���X
					sizeof(sockaddr));			// �A�h���X�\���̂̃o�C�g�T�C�Y
			}
			else
			{
				printf("��M�f�[�^ : %s %d \n", m_messageData.receiveMessage, m_messageData.randNum);
				printf("���M���h�o�A�h���X/�|�[�g�ԍ� %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));
				
				
				char* context;
				char* msgType = strtok_s(m_messageData.receiveMessage, " ", &context);
				int msgTypeNo = strtof(msgType, NULL);

				// ���b�Z�[�W�̃^�C�v�ɂ��A�����𕪊�
				switch (msgTypeNo)
				{
					// �R���|�[�l���g�̒l�X�V
					case yUno_SystemManager::yUno_NetWorkManager::MessageType::UpdateComponentValue:
					{
						// �c��̏���ǂݎ��
						char* objName = strtok_s(NULL, " ", &context);
						char* comType = strtok_s(NULL, " ", &context);
						char* varName = strtok_s(NULL, " ", &context);
						char* xParam = strtok_s(NULL, " ", &context);
						char* yParam = strtok_s(NULL, " ", &context);
						char* zParam = strtok_s(NULL, " ", &context);
						if (objName != nullptr && xParam != nullptr && yParam != nullptr && zParam != nullptr)
						{
							float newX = strtof(xParam, NULL);
							float newY = strtof(yParam, NULL);
							float newZ = strtof(zParam, NULL);
							SceneManager::GetNowScene()->GetSceneObject(objName)->transform->Position = Vector3(newX, newY, newZ);
							memcpy(g_rockObject, objName, strlen(objName));
						}
						break;
					}
					case yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject:
					{
						// �c��̏���ǂݎ��
						char* objName = strtok_s(NULL, " ", &context);
						strcpy_s(rockObjectName, objName);
						break;
					}
				}
			}
		}
		// �ʐM���I�������H
		else if (!m_isCommunicationData)
		{
			// ���[�v�𔲂���
			break;
		}
		else
		{
			std::cout << "�G���[����������" << std::endl;
		}
	}
	return;
}

void Server::TestThread()
{
	//std::array<std::list<GameObject*>, 4> lateSceneObject = SceneManager::GetSceneObjectAll();
	//std::list<GameObject> lateObjects;
	//Transform moveObject;

	//for (auto& lateObjectList : lateSceneObject)
	//{
	//	for (auto& lateObject : lateObjectList)
	//	{
	//		lateObjects.push_back(*lateObject);
	//	}
	//}

	//while (true)
	//{
	//	if (!m_isCommunicationData)
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		for (auto& lateObject : lateObjects)
	//		{
	//			auto object = SceneManager::GetNowScene()->GetSceneObject(lateObject.GetName());

	//			if (lateObject.transform->Position != object->transform->Position &&
	//				strcmp(lateObject.GetName(), "SpectatorCamera") != 0 && (g_rockObject == NULL || strcmp(lateObject.GetName(), g_rockObject) != 0))
	//			{
	//				char sendData[100];
	//				sprintf_s(sendData, "%s %f %f %f", lateObject.GetName(), object->transform->Position.x, object->transform->Position.y, object->transform->Position.z);
	//				SendData(sendData);
	//				lateObject = *object;
	//			}
	//		}
	//	}
	//}
}

Server::~Server()
{
	// �ʐM���s���Ă���H
	if (m_isCommunicationData)
		// �T�[�o�[�����
		CloseServer();
}

void Server::OpenServer()
{
	// �ʐM���s���Ă��Ȃ��H
	if (!m_isCommunicationData)
	{
		WSADATA wsaData;	// WinSock�̏������f�[�^���i�[
		WORD	verNo;		// �o�[�W�����w��
		int sts;			// WinSock�����������������ꂽ�����

		// �o�[�W����2.2��v��
		verNo = MAKEWORD(2, 2);

		// WinSock���������A�G���[�����������H
		if (WSAStartup(
			verNo,	// �v���o�[�W����
			&wsaData)	// WinSock�f�[�^���i�[���邽�߂̕ϐ�
			== SOCKET_ERROR)
		{
			int errorCode = WSAGetLastError();
			std::cout << "WSAStartup() Failed!!! ErrorCode�F" << errorCode << std::endl;
			return;
		}

		// �v�������o�[�W���������p�ł��Ȃ��H
		if (verNo != wsaData.wVersion)
		{
			std::cout << "�v�������o�[�W�����͗��p�ł��܂���" << std::endl;
			return;
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
			return;
		}

		// ���g�̃A�h���X��ݒ�
		sockaddr_in myAddress{};	// ���g�̃A�h���X
		myAddress.sin_port = htons(PORTNO);
		myAddress.sin_family = AF_INET;
		myAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

		std::cout << ntohs(myAddress.sin_port) << std::endl;

		// �����̃\�P�b�g��IP�A�h���X�A�|�[�g�ԍ������蓖�Ă�
		sts = bind(m_mySocket, (sockaddr*)&myAddress, sizeof(sockaddr));
		if (sts == SOCKET_ERROR)
		{
			std::cout << "�\�P�b�g�ւ̊��蓖�ĂɎ��s���܂���" << std::endl;
			return;
		}
		// �ʐM�̊J�n��ݒ�
		m_isCommunicationData = true;
		// �n�ʂ�ݒ�
		m_myServerRank = Owner;

		// ��M�X���b�h����
		m_receiveThread = std::thread(&Server::ReceiveThread, this);
		testThread = std::thread(&Server::TestThread, this);

		std::cout << "NetWork Communication Start" << std::endl;
	}
}

void Server::CloseServer()
{
	// �f�[�^�̒ʐM���s���Ă���H
	if (m_isCommunicationData)
	{
		//�@�\�P�b�g���N���[�Y���A�G���[�����������H
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode�F" << errorCode << std::endl;
		}
		// �ʐM�̏I����ݒ�
		m_isCommunicationData = false;

		// �X���b�h�̏I����҂�
		m_receiveThread.join();
		testThread.join();

		// WINSOCK�̏I������
		WSACleanup();

		std::cout << "NetWork Communication End" << std::endl;
	}
}

void Server::LoginServer()
{
	if (!m_isCommunicationData)
	{
		WSADATA wsaData;	// WinSock�̏������f�[�^���i�[
		WORD	verNo;		// �o�[�W�����w��
		int sts;			// WinSock�����������������ꂽ�����

		verNo = MAKEWORD(2, 2);	// 2.2��v��

		// WinSock���������A�G���[�����������H
		if (WSAStartup(
			verNo,		// �v���o�[�W����
			&wsaData)	// WinSock�f�[�^���i�[���邽�߂̕ϐ�
			== SOCKET_ERROR)
		{
			int errorCode = WSAGetLastError();
			std::cout << "WSAStartup() Failed!!! ErrorCode�F" << errorCode << std::endl;
			return;
		}

		// �v�������o�[�W���������p�ł��Ȃ��H
		if (verNo != wsaData.wVersion)
		{
			std::cout << "�v�������o�[�W�����͗��p�ł��܂���" << std::endl;
			return;
		}

		// �\�P�b�g����
		m_mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		// �\�P�b�g�������A�G���[�����������H
		if (m_mySocket == INVALID_SOCKET)
		{
			std::cout << "�\�P�b�g�̐����Ɏ��s���܂���" << std::endl;
			return;
		}

		printf("\n����IP�A�h���X����͂��Ă�������\n");

		char str[256];
		rewind(stdin);
		int r = scanf_s("%s", str, 250);

		// ����̃A�h���X��ݒ�
		m_sendAddress.sin_port = htons(PORTNO);	// �|�[�g�ԍ��i16�r�b�g�j���l�b�g���[�N�o�C�g�I�[�_�[�ɕύX
		m_sendAddress.sin_family = AF_INET;
		// 10�i�\�L��IP�A�h���X��32�r�b�g�ɕϊ��i�l�b�g���[�N�o�C�g�I�[�_�[�j
		m_sendAddress.sin_addr.S_un.S_addr = inet_addr(str);

		// �ʐM�̊J�n��ݒ�
		m_isCommunicationData = true;
		// �n�ʂ�ݒ�
		m_myServerRank = User;

		// ��M�X���b�h����
		m_receiveThread = std::thread(&Server::ReceiveThread, this);
		testThread = std::thread(&Server::TestThread, this);
	}
}

void Server::LogoutServer()
{
	// �ʐM���s���Ă���H
	if (m_isCommunicationData)
	{
		//�@�\�P�b�g���N���[�Y���A�G���[�����������H
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode�F" << errorCode << std::endl;
		}
		// �ʐM�̏I����ݒ�
		m_isCommunicationData = false;

		// �X���b�h�̏I����҂�
		m_receiveThread.join();

		// WINSOCK�̏I������
		WSACleanup();
	}
	std::cout << "Logout Server" << std::endl;
}

void Server::SendData()
{
	if (m_isCommunicationData)
	{
		// ���M�f�[�^�쐬
		printf("\n���M�f�[�^����͂��Ă��������i�A���t�@�x�b�g�̂݁j\n");
		rewind(stdin);
		int r = scanf_s("%[^\n]", m_messageData.sendMessage, 255);	// ���s�ȊO��ǂݍ���

		size_t len = strlen(m_messageData.sendMessage);		// ���M�����񒷂��擾

		// �f�[�^�̑��M���A�G���[�����������H
		if (sendto(
			m_mySocket,							// �\�P�b�g�ԍ�
			m_messageData.sendMessage,			// ���M�f�[�^
			len,								// ���M�f�[�^��
			0,									// �t���O
			(sockaddr*)&m_sendAddress,			// ���M��A�h���X
			sizeof(sockaddr))					// �A�h���X�\���̂̃o�C�g��
			== SOCKET_ERROR)
		{
			std::cout << "�f�[�^�̑��M�Ɏ��s���܂���" << std::endl;
		}
	}
}

void Server::SendData(const char* message)
{
	if (m_isCommunicationData)
	{
		strcpy_s(m_messageData.sendMessage, sizeof(m_messageData.sendMessage), message);
		size_t len = strlen(m_messageData.sendMessage);		// ���M�����񒷂��擾


		// �f�[�^�̑��M���A�G���[�����������H
		if (sendto(
			m_mySocket,							// �\�P�b�g�ԍ�
			m_messageData.sendMessage,			// ���M�f�[�^
			len,								// ���M�f�[�^��
			0,									// �t���O
			(sockaddr*)&m_sendAddress,			// ���M��A�h���X
			sizeof(sockaddr))					// �A�h���X�\���̂̃o�C�g��
			== SOCKET_ERROR)
		{
			std::cout << "�f�[�^�̑��M�Ɏ��s���܂���" << std::endl;
		}
	}
}

bool Server::IsRockObject(const char* objectName)
{
	// ���b�N����Ă��Ȃ��H�ʂ̃I�u�W�F�N�g�����b�N���Ă���H
	if (rockObjectName == nullptr || strcmp(rockObjectName, objectName) != 0)
		return false;
	return true;
}
