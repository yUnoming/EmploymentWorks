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

		memset(m_receiveData.data, 0, sizeof(m_receiveData.data));

		int sts = recvfrom(
			m_mySocket,
			(char*)m_receiveData.data,
			sizeof(m_receiveData.data),
			0,
			(sockaddr*)&m_sendAddress,
			&myAddressLength);

		if (sts != SOCKET_ERROR)
		{
			if (strcmp(m_receiveData.data, "LoginSuccess") == 0)
			{
				std::cout << "Login Server" << std::endl;
			}
			else if (strcmp(m_receiveData.data, "ServerLogin") == 0)
			{
				printf("��M�f�[�^ : %s \n", m_receiveData.data);
				printf("���M���h�o�A�h���X/�|�[�g�ԍ� %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));

				strcpy_s(m_sendData.data, sizeof(m_sendData.data), "LoginSuccess");
				int len = static_cast<int>(strlen(m_sendData.data));	// ���M�����񒷂��擾
				sts = sendto(
					m_mySocket,					// �\�P�b�g�ԍ�
					m_sendData.data,			// ���M�f�[�^
					len,						// ���M�f�[�^��
					0,							// �t���O
					(sockaddr*)&m_sendAddress,	// ���M��A�h���X
					sizeof(sockaddr));			// �A�h���X�\���̂̃o�C�g�T�C�Y
			}
			else
			{
				printf("��M�f�[�^ : %s\n", m_receiveData.data);
				printf("���M���h�o�A�h���X/�|�[�g�ԍ� %s/%d \n",
					inet_ntoa(m_sendAddress.sin_addr),
					ntohs(m_sendAddress.sin_port));
				
				// ===== ���b�Z�[�W�̎�ނɂ���ď����𕪊� ===== //
				switch (m_receiveData.message.header.type)
				{
					// �ʐM�J�n
					case MessageType::CommunicationStart:
					{
						// ----- �ʐM��������X�g�Ɋi�[ ----- //
						// �ʐM����̏���ۑ�����
						CommunicationUserData comUser;
						comUser.userRank = (ServerRank)m_sendData.message.header.userRank;
						comUser.address = m_sendAddress;
						
						// ���X�g�Ɋi�[
						m_comUserList.push_back(comUser);

						// ----- ����ɒʐM������`���� ----- //
						m_sendData.message.header.type = MessageType::CommunicationSuccess;
						SendMessageData(m_sendData);
						break;
					}

					// �ʐM����
					case MessageType::CommunicationSuccess:
						// �ʐM�̊J�n��ݒ�
						m_isCommunicationData = true;
						// �V�X�e���ʒm��\��
						MessageBoxW(NULL, L"�T�[�o�[�Ƀ��O�C�����܂���", L"�V�X�e���ʒm", MB_OK);
						break;
					// �ʐM�I��
					case MessageType::CommunicationEnd:
						// �ʐM���̃��[�U�[���������[�v
						for (auto it = m_comUserList.begin(); it != m_comUserList.end(); it++)
						{
							CommunicationUserData comUser = *it;
							// IP�A�h���X�ƃ|�[�g�ԍ������M���Ɠ����H
							if (comUser.address.sin_addr.S_un.S_addr == m_sendAddress.sin_addr.S_un.S_addr &&
								comUser.address.sin_port == m_sendAddress.sin_port)
							{
								// ���X�g���珜�O
								m_comUserList.erase(it);

								// ���b�Z�[�W�ʒm
								if (m_myServerRank == ServerRank::Owner)
									MessageBoxW(NULL, L"���[�U�[�����O�A�E�g���܂���", L"�V�X�e���ʒm", MB_OK);
								else if(m_myServerRank == ServerRank::User)
									MessageBoxW(NULL, L"�T�[�o�[�����܂���", L"�V�X�e���ʒm", MB_OK);
								break;
							}
						}
						break;

					// �R���|�[�l���g�X�V
					case MessageType::UpdateComponent:
						// ===== �R���|�[�l���g�̎�ނɂ���ď����𕪊� ===== //
						// Transform�R���|�[�l���g
						if (strcmp(m_receiveData.message.body.componentType,
							"class PublicSystem::Transform") == 0)
						{
							// �R���|�[�l���g�擾
							Transform* transform =
								SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->transform;
							// �e�l����
							transform->Position = m_receiveData.message.body.transform.Position;
							transform->Rotation = m_receiveData.message.body.transform.Rotation;
							transform->Scale = m_receiveData.message.body.transform.Scale;
						}
						// Text�R���|�[�l���g
						else if (strcmp(m_receiveData.message.body.componentType,
							"class PublicSystem::Text") == 0)
						{
							// �R���|�[�l���g�擾
							Text* text =
								SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->GetComponent<Text>();
							// �e�l����
							text->text = m_receiveData.message.body.text.text;
							text->fontSize = m_receiveData.message.body.text.fontSize;
						}
						break;

					// �I�u�W�F�N�g�I��
					case MessageType::ClickObject:
						// �N���b�N���ꂽ�I�u�W�F�N�g������
						strcpy_s(rockObjectName, m_receiveData.message.body.object.GetName());
						break;
				}
			}
		}
		// �ʐM���I�������H
		else if (!m_isCommunicationData)
		{
			// ���[�v�𔲂���
			break;
		}
	}
	return;
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

		MessageBoxW(NULL, L"�T�[�o�[���J���܂���", L"�V�X�e���ʒm", MB_OK);
	}
}
 
void Server::CloseServer()
{
	// �f�[�^�̒ʐM���s���Ă���H
	if (m_isCommunicationData)
	{
		// ===== �ʐM�I���𑊎�ɒʒm ===== //
		// �ʐM���肪����H
		if (!m_comUserList.empty())
		{
			// ���b�Z�[�W���M
			MessageData messageData;
			messageData.message.header.type = MessageType::CommunicationEnd;
			SendMessageData(messageData);
		}
		
		// ===== �T�[�o�[�N���[�Y���� ===== //
		//�@�\�P�b�g���N���[�Y���A�G���[�����������H
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode�F" << errorCode << std::endl;
		}
		// �ʐM�̏I����ݒ�
		m_isCommunicationData = false;
		// ���b�N��Ԃ̉���
		ZeroMemory(rockObjectName, sizeof(rockObjectName));

		// �X���b�h�̏I����҂�
		m_receiveThread.join();

		// WINSOCK�̏I������
		WSACleanup();

		MessageBoxW(NULL, L"�T�[�o�[����܂���", L"�V�X�e���ʒm", MB_OK);
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

		// �n�ʂ�ݒ�
		m_myServerRank = User;

		// �X���b�h����������Ă��Ȃ��H
		if(!m_receiveThread.joinable())
			// ��M�X���b�h����
			m_receiveThread = std::thread(&Server::ReceiveThread, this);

		// ����ɒʐM�J�n�ʒm�𑗂�
		m_sendData.message.header.type = MessageType::CommunicationStart;
		SendMessageData(m_sendData);
	}
}

void Server::LogoutServer()
{
	// �ʐM���s���Ă���H
	if (m_isCommunicationData)
	{
		// ===== �ʐM�I���𑊎�ɒʒm ===== //
		MessageData messageData;
		messageData.message.header.type = MessageType::CommunicationEnd;
		SendMessageData(messageData);

		//�@�\�P�b�g���N���[�Y���A�G���[�����������H
		if (closesocket(m_mySocket) != 0)
		{
			int errorCode = WSAGetLastError();
			std::cout << "closesocket() Failed!!! ErrorCode�F" << errorCode << std::endl;
		}
		// �ʐM�̏I����ݒ�
		m_isCommunicationData = false;
		// ���b�N��Ԃ̉���
		ZeroMemory(rockObjectName, sizeof(rockObjectName));

		// �X���b�h�̏I����҂�
		m_receiveThread.join();

		// WINSOCK�̏I������
		WSACleanup();
	}
	MessageBoxW(NULL, L"�T�[�o�[���烍�O�A�E�g���܂���", L"�V�X�e���ʒm", MB_OK);
}

void Server::SendData()
{
	if (m_isCommunicationData)
	{
		// ���M�f�[�^�쐬
		printf("\n���M�f�[�^����͂��Ă��������i�A���t�@�x�b�g�̂݁j\n");
		rewind(stdin);
		int r = scanf_s("%[^\n]", m_sendData.data, 255);	// ���s�ȊO��ǂݍ���

		size_t len = strlen(m_sendData.data);		// ���M�����񒷂��擾

		// �f�[�^�̑��M���A�G���[�����������H
		if (sendto(
			m_mySocket,							// �\�P�b�g�ԍ�
			m_sendData.data,					// ���M�f�[�^
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

void Server::SendMessageData(MessageData& messageData)
{
	if (m_isCommunicationData)
	{
		// ===== ���̑��ɑ�������� ===== //
		// ���[�U�[�����N
		messageData.message.header.userRank = m_myServerRank;

		// ===== ���M���� ===== //
		// �f�[�^�̑��M���A�G���[�����������H
		if (sendto(
			m_mySocket,							// �\�P�b�g�ԍ�
			messageData.data,					// ���M�f�[�^
			sizeof(messageData.data),			// ���M�f�[�^��
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
