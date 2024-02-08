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

#include "SystemNetWorkManager.h"
#include "SceneManager.h"
#include "TemplateCube.h"
#include "TemplateText.h"
#include "Time.h"

#include <stdio.h>
#include <time.h>
#include <iostream>

char g_rockObject[256]{};

void Ctlan::PrivateSystem::Server::ReceiveThread()
{
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
#if _DEBUG
			printf("���M���h�o�A�h���X/�|�[�g�ԍ� %s/%d \n",
				inet_ntoa(m_sendAddress.sin_addr),
				ntohs(m_sendAddress.sin_port));
#endif
			// ===== ���b�Z�[�W�̎�ނɂ���ď����𕪊� ===== //
			switch (m_receiveData.message.header.type)
			{
				//----------//
				// �ʐM�J�n //
				case MessageType::CommunicationStart:
				{
					// ----- �ʐM��������X�g�Ɋi�[ ----- //
					// �ʐM����̏���ۑ�����
					CommunicationUserData comUser;						// �ʐM���[�U�[���
					comUser.userRank =									// ���[�U�[�����N
						(ServerRank)m_sendData.message.header.userRank;
					int userNo = 1;										// ���[�U�[�ԍ�(�P�Ԃ���m�F)
					bool success = true;								// ���[�U�[�ԍ������܂������ǂ���

					// ���[�U�[�ԍ������܂�܂Ń��[�v
					do
					{
						success = true;
						// ���݃��O�C�����Ă��郆�[�U�[�����[�v
						for (const CommunicationUserData& data : m_comUserList)
						{
							// ���[�U�[�ԍ��������[�U�[�Ɣ�����H
							if (data.userNo == userNo)
							{
								userNo++;		// �ԍ������Z
								success = false;// �ēx���[�v����悤�ɕύX
								break;
							}
						}
					} while (!success);

					// �l���
					m_sendData.message.header.userRank = User;
					m_sendData.message.header.userNo = userNo;
					comUser.userNo = userNo;
					comUser.address = m_sendAddress;
					// ���X�g�Ɋi�[
					m_comUserList.push_back(comUser);

					// ----- ����ɒʐM������`���� ----- //
					m_sendData.message.header.type = MessageType::CommunicationSuccess;
					SendMessageData(m_sendData);
					break;
				}
				//----------//
				// �ʐM���� //
				case MessageType::CommunicationSuccess:
					if (!m_isCommunicationData)
					{
						// �ʐM�̊J�n��ݒ�
						m_isCommunicationData = true;
						m_isCommunicationDuring = false;
						// ���g�̔ԍ�����
						m_myServerNo = m_receiveData.message.header.userNo;
						// �V�X�e���ʒm��\��
						MessageBoxW(NULL, L"�T�[�o�[�Ƀ��O�C�����܂���", L"�V�X�e���ʒm", MB_OK);
						break;
					}
				//----------//
				// �ʐM�I�� //
				case MessageType::CommunicationEnd:
					// �I�[�i�[�̏ꍇ
					if (m_myServerRank == ServerRank::Owner)
					{
						// �폜���郆�[�U�[�C�e���[�^�[
						std::list<CommunicationUserData>::iterator eraseUser;

						// �ʐM���̃��[�U�[���������[�v
						for (auto it = m_comUserList.begin(); it != m_comUserList.end(); it++)
						{
							CommunicationUserData comUser = *it;
							// IP�A�h���X�ƃ|�[�g�ԍ������M���Ɠ����H
							if (comUser.address.sin_addr.S_un.S_addr == m_sendAddress.sin_addr.S_un.S_addr &&
								comUser.address.sin_port == m_sendAddress.sin_port)
							{
								// ===== ���b�N��Ԃ̉��� ===== //
								std::list<std::list<RockObjectData>::iterator> eraseIteratorList;	// �폜����v�f���i�[���Ă������X�g

								// ���b�N����Ă���I�u�W�F�N�g�����[�v
								for (auto it = m_rockObjectList.begin(); it != m_rockObjectList.end(); it++)
								{
									RockObjectData rockObject = *it;
									// ���b�N���Ă��郆�[�U�[�Ƒ��M�����[�U�[����v�H
									if (rockObject.rockUserNo == m_receiveData.message.header.userNo)
									{
										eraseIteratorList.push_back(it);	// �폜����v�f�Ƃ��Ċi�[
									}
								}
								// �폜����v�f�����[�v
								for (auto it : eraseIteratorList)
								{
									m_rockObjectList.erase(it);	// �v�f���폜

									// �����[�U�[�̃��b�N��Ԃ�����
									m_receiveData.message.header.type = MessageType::ClickObject;
									m_receiveData.message.body.object.CopyName(nullptr);
									SendMessageOtherUser(m_receiveData);
								}

								// �폜���郆�[�U�[�̃C�e���[�^�[����
								eraseUser = it;
							}
						}
						// ���[�U�[���X�g���珜�O
						m_comUserList.erase(eraseUser);
						// �V�X�e���ʒm
						MessageBoxW(NULL, L"���[�U�[�����O�A�E�g���܂���", L"�V�X�e���ʒm", MB_OK);
					}
					// ���[�U�[�̏ꍇ
					else if (m_myServerRank == ServerRank::User)
					{
						// �V���b�g�_�E�����ꂽ���Ƃ��L�^
						m_isServerShutdown = true;
						// �V�X�e���ʒm
						MessageBoxW(NULL, L"�T�[�o�[�����܂���", L"�V�X�e���ʒm", MB_OK);
					}
					break;
				//--------------------//
				// �R���|�[�l���g�X�V //
				case MessageType::UpdateComponent:
					// ===== �R���|�[�l���g�̎�ނɂ���ď����𕪊� ===== //
					// Transform�R���|�[�l���g
					if (strcmp(m_receiveData.message.body.componentType, "Transform") == 0)
					{
						// �R���|�[�l���g�擾
						Transform* transform =
							Ctlan::PublicSystem::SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->transform;
						// �e�l����
						*transform = Transform(m_receiveData.message.body.transform);
					}
					// Text�R���|�[�l���g
					else if (strcmp(m_receiveData.message.body.componentType, "Text") == 0)
					{
						// �R���|�[�l���g�擾
						Text* text =
							SceneManager::GetNowScene()->GetSceneObject(m_receiveData.message.body.object.GetName())->GetComponent<Text>();
						// �e�l����
						*text = Text(m_receiveData.message.body.text);
					}
					SendMessageOtherUser(m_receiveData);
					break;
				//------------------//
				// �I�u�W�F�N�g�I�� //
				case MessageType::ClickObject:
				{
					bool isRocked = false;	// ���Ƀ��b�N����Ă��邩�ǂ���

					// ���b�N����Ă���I�u�W�F�N�g�����[�v
					for (RockObjectData& rockObject : m_rockObjectList)
					{
						// ���M�����[�U�[�͊��ɃI�u�W�F�N�g�����b�N���Ă���H
						if (rockObject.rockUserNo == m_receiveData.message.header.userNo)
						{
							// �N���b�N���ꂽ�I�u�W�F�N�g������
							strcpy_s(rockObject.rockObjectName, m_receiveData.message.body.object.GetName());
							isRocked = true;	// ���Ƀ��b�N���Ă��邱�Ƃ��o���Ă���
							break;
						}
					}
					// �܂����b�N����Ă��Ȃ��I�u�W�F�N�g�H
					if (!isRocked)
					{
						// �o�^����
						RockObjectData rockObjectData;
						// �N���b�N���ꂽ�I�u�W�F�N�g������
						strcpy_s(rockObjectData.rockObjectName, m_receiveData.message.body.object.GetName());
						rockObjectData.rockUserNo = m_receiveData.message.header.userNo;
						m_rockObjectList.push_back(rockObjectData);
					}

					SendMessageOtherUser(m_receiveData);	// �����[�U�[�Ƀ��b�Z�[�W���M
					break;
				}
				//------------------//
				// �I�u�W�F�N�g�폜 //
				case MessageType::ObjectDelete:
					// ��M�f�[�^������I�u�W�F�N�g�����擾���A���̃I�u�W�F�N�g���폜
					Ctlan::PublicSystem::SceneManager::GetNowScene()->DeleteSceneObject(m_receiveData.message.body.object.GetName());
					SendMessageOtherUser(m_receiveData);
					break;
				//--------------//
				// �L���[�u�쐬 //
				case MessageType::CreateCube:
				{
					// �L���[�u���쐬���A�쐬�����L���[�u���擾���Ă���
					GameObject* cubeObject = Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateCube>(1, "Cube");
					// ���b�Z�[�W����Transform�����擾���A���
					// ���쐬�����ہA���W�ȊO�͈��̒l�Ȃ̂ŁA������Ȃ�
					cubeObject->transform->position = m_receiveData.message.body.transform.position;
					SendMessageOtherUser(m_receiveData);
					break;
				}
				//--------------//
				// �e�L�X�g�쐬 //
				case MessageType::CreateText:
				{
					// �e�L�X�g���쐬
					Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateText>(3, "Text");
					SendMessageOtherUser(m_receiveData);
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

void Server::CommunicationStartThread()
{
	double timer = 0;			// ���b�Z�[�W�𑗂�܂ł̎���
	int sendMessageCount = 0;	// ���b�Z�[�W�𑗂�����
	// �ʐM����or�K��񐔃��b�Z�[�W�𑗂�܂Ń��[�v
	while (!m_isCommunicationData && sendMessageCount <= 10)
	{
		// ����b�����o�߂����H
		if (timer >= 1000000)
		{
			// ����ɒʐM�J�n�ʒm�𑗂�
			m_sendData.message.header.type = MessageType::CommunicationStart;
			SendMessageData(m_sendData);
			sendMessageCount++;
			timer = 0;
		}
		else
		{
			// �^�C�}�[�̕b���𑝂₷
			timer += Ctlan::PublicSystem::Time::DeltaTime * 0.00006f;
		}
	}

	// ���b�Z�[�W�𑗂������A�ԓ����Ȃ������H
	if (!m_isCommunicationData)
		m_isCommunicationDuring = false;
		// ���b�Z�[�W�ʒm
		MessageBoxW(NULL, L"���O�C���Ɏ��s���܂���", L"�V�X�e���ʒm", MB_OK);
	return;
}

void Server::SendMessageOtherUser(MessageData& sendMessage)
{
	// ���g���T�[�o�[���J�����H
	if (m_myServerRank == Owner)
	{
		// ���[�U�[�������l����H
		if (m_comUserList.size() > 1)
		{
			// ���[�U�[���������[�v
			for (const CommunicationUserData& data : m_comUserList)
			{
				// ���M�����[�U�[�ł͂Ȃ����[�U�[�H
				if (data.userNo != sendMessage.message.header.userNo)
				{
					m_sendAddress = data.address;	// �A�h���X�ݒ�
					SendMessageData(sendMessage);	// ���b�Z�[�W���M
				}
			}
		}
	}
}

Server::~Server()
{
	// �ʐM���s���Ă���H
	if (m_isCommunicationData)
	{
		// ���g�̒n�ʂɂ���ď����𕪂���
		switch (m_myServerRank)
		{
			//----------//
			// ���[�U�[ //
			case User:
				LogoutServer();
				break;
			//----------//
			// �I�[�i�[ //
			case Owner:
				CloseServer();
				break;
		}
	}

	if(m_receiveThread.joinable())
		// ��M�X���b�h�I��
		m_receiveThread.join();
	if (m_comStartThread.joinable())
		m_comStartThread.join();
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

		// ��M�X���b�h����������Ă��Ȃ��H
		if (!m_receiveThread.joinable())
			// ��M�X���b�h����
			m_receiveThread = std::thread(&Server::ReceiveThread, this);

		MessageBoxW(NULL, L"�T�[�o�[���J���܂���", L"�V�X�e���ʒm", MB_OK);
	}
}
 
void Server::CloseServer()
{
	// �I�[�i�[�Ƃ��āA�f�[�^�̒ʐM���s���Ă���H
	if (m_isCommunicationData && m_myServerRank == Owner)
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
		m_isCommunicationDuring = false;
		// ���b�N��Ԃ̉���
		m_rockObjectList.clear();

		// �X���b�h�̏I����҂�
		m_receiveThread.join();

		// WINSOCK�̏I������
		WSACleanup();

		MessageBoxW(NULL, L"�T�[�o�[����܂���", L"�V�X�e���ʒm", MB_OK);
	}
	else
	{
		// ���b�Z�[�W�\��
		MessageBoxW(NULL, L"���Ȃ��̓T�[�o�[���J���Ă��܂���", L"�V�X�e���ʒm", MB_OK);
	}
}

void Server::LoginServer()
{
	// �ʐM���s���Ă��Ȃ��H
	if (!m_isCommunicationData && !m_isCommunicationDuring)
	{
		WSADATA wsaData;	// WinSock�̏������f�[�^���i�[
		WORD	verNo;		// �o�[�W�����w��

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

		char str[256]{};
		rewind(stdin);
		int r = scanf_s("%s", str, 256);

		// ����̃A�h���X��ݒ�
		m_sendAddress.sin_port = htons(PORTNO);	// �|�[�g�ԍ��i16�r�b�g�j���l�b�g���[�N�o�C�g�I�[�_�[�ɕύX
		m_sendAddress.sin_family = AF_INET;
		// 10�i�\�L��IP�A�h���X��32�r�b�g�ɕϊ��i�l�b�g���[�N�o�C�g�I�[�_�[�j
		m_sendAddress.sin_addr.S_un.S_addr = inet_addr(str);

		// �n�ʂ�ݒ�
		m_myServerRank = User;
		// �ʐM�J�n���̏�ԂɕύX
		m_isCommunicationDuring = true;

		// ��M�X���b�h����������Ă��Ȃ��H
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
	// ���[�U�[�Ƃ��āA�ʐM���s���Ă���H
	if (m_isCommunicationData && m_myServerRank == User)
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
		// �ʐM��Ԃ�������
		m_isCommunicationData = false;
		m_isCommunicationDuring = false;
		// �V���b�g�_�E����Ԃ�������
		m_isServerShutdown = false;
		// ���b�N��Ԃ̉���
		m_rockObjectList.clear();

		// �X���b�h�̏I����҂�
		if(m_receiveThread.joinable())
			m_receiveThread.join();

		// WINSOCK�̏I������
		WSACleanup();

		// ���b�Z�[�W�\��
		MessageBoxW(NULL, L"�T�[�o�[���烍�O�A�E�g���܂���", L"�V�X�e���ʒm", MB_OK);
	}
	else
	{
		// ���b�Z�[�W�\��
		MessageBoxW(NULL, L"���Ȃ��̓T�[�o�[�Ƀ��O�C�����Ă��܂���", L"�V�X�e���ʒm", MB_OK);
	}
}

void Server::SendMessageData(MessageData& messageData)
{
	if (m_isCommunicationData || messageData.message.header.type == MessageType::CommunicationStart)
	{
		// ===== ���̑��ɑ�������� ===== //
		// �T�[�o�[�����M���ȊO�̃��[�U�[�Ƀ��b�Z�[�W�𑗂�H
		if (m_myServerRank == Owner && messageData.message.header.userRank == User)
		{
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
			return;	// �������I��
		}
		// �ʏ폈��
		else
		{
			// �e�l����
			// ���[�U�[�����N
			messageData.message.header.userRank = m_myServerRank;
			// ���[�U�[�ԍ�
			messageData.message.header.userNo = m_myServerNo;
		}

		// ===== ���M���� ===== //
		// �����l�̃��[�U�[�ƒʐM���Ă���H
		if (m_comUserList.size() > 1)
		{
			// ���[�U�[���������[�v
			for (const CommunicationUserData& data : m_comUserList)
			{
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
		else
		{
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
}

const int Server::GetRockUserNo(const char* objectName)
{
	// ���b�N���Ă��Ȃ��H
	if (m_rockObjectList.empty())
		return m_myServerNo;

	// ���b�N���Ă���I�u�W�F�N�g�����[�v
	for (const RockObjectData& rockObject : m_rockObjectList)
	{
		// �I�u�W�F�N�g�������b�N���Ă���I�u�W�F�N�g���ƈ�v�����H
		if (rockObject.rockObjectName != nullptr && strcmp(rockObject.rockObjectName, objectName) == 0)
			return rockObject.rockUserNo;
	}
	return m_myServerNo;
}

bool Server::IsRockObject(const char* objectName)
{
	// ���b�N���Ă��Ȃ��H
	if (m_rockObjectList.empty())
		return false;

	// ���b�N���Ă���I�u�W�F�N�g�����[�v
	for (const RockObjectData& rockObject : m_rockObjectList)
	{
		// �I�u�W�F�N�g�������b�N���Ă���I�u�W�F�N�g���ƈ�v�����H
		if (rockObject.rockObjectName != nullptr && strcmp(rockObject.rockObjectName, objectName) == 0)
			return true;
	}
	return false;
}
