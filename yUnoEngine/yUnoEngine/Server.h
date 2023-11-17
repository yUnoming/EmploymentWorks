#pragma once
/**
* @file		Server.h
* @brief	Server�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.16
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <WinSock2.h>
#include <thread>


/// <summary>
///	�T�[�o�[���������߂̃N���X	</summary>
class Server
{
	private:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		///	���g�̃\�P�b�g���	</summary>
		SOCKET m_mySocket;
		/// <summary>
		///	��M�X���b�h	</summary>
		std::thread m_receiveThread;
		/// <summary>
		///	��M�o�b�t�@	</summary>
		char m_receiveBuffer[65535]{};
		/// <summary>
		/// ���M�o�b�t�@	</summary>
		char m_sendBuffer[256] = { "�f�[�^��M���܂���" };

		/// <summary>
		/// �T�[�o�[���J���Ă��邩�ǂ��� </summary>
		bool isOpenServer;


		// ----- functions / �֐� ----- //
		/// <summary>
		/// ��M�X���b�h	</summary>
		void ReceiveThread();


	public:
		// ----- functions / �֐� ----- //
		// �f�X�g���N�^
		~Server();

		/// <summary>
		///	�T�[�o�[���J��	</summary>
		void OpenServer();
		/// <summary>
		///	�T�[�o�[�����	</summary>
		void CloseServer();
};

