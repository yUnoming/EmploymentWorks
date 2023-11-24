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
		// ----- structs / �\���� ----- //
		/// <summary>
		///	����M�p�̃��b�Z�[�W	</summary>
		struct MessageData
		{
			int randNum = 0;
			char receiveMessage[65535];
			char sendMessage[256];
		};

		// ---- enums / �񋓌^ ----- //
		/// <summasy>
		/// �T�[�o�[�ł̒n�� </summary>
		enum ServerRank
		{
			/// <summary>
			///	�T�[�o�[�𗧂Ă��l��	</summary>
			Owner,
			/// <summary>
			///	�T�[�o�[�ɗ����l��	</summary>
			User
		};
		
		// ----- variables / �ϐ� ----- //
		/// <summary>
		///	���g�̃\�P�b�g���	</summary>
		SOCKET m_mySocket;
		/// <summary>
		///	���g�̃A�h���X	</summary>
		sockaddr_in m_myAddress{};
		/// <summary>
		///	���M��A�h���X	</summary>
		sockaddr_in m_sendAddress{};

		/// <summary>
		///	��M�X���b�h	</summary>
		std::thread m_receiveThread;
		/// <summary>
		///	����M���b�Z�[�W	</summary>
		MessageData m_messageData;

		/// <summary>
		/// �f�[�^�̒ʐM��� </summary>
		bool m_isCommunicationData;
		/// <summary>
		///	���g�̃T�[�o�[�ł̒n��	</summary>
		ServerRank m_myServerRank;

		// ���b�N���Ă���I�u�W�F�N�g��
		char rockObjectName[30];

		// ----- functions / �֐� ----- //
		/// <summary>
		/// ��M�X���b�h	</summary>
		void ReceiveThread();
		
		void TestThread();
		std::thread testThread;


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
		/// <summary>
		///	�T�[�o�[�Ƀ��O�C������	</summary>
		void LoginServer();
		/// <summary>
		///	�T�[�o�[���烍�O�A�E�g����	</summary>
		void LogoutServer();
		/// <summary>
		/// �f�[�^�𑗐M����	</summary>
		void SendData();
		/// <summary>
		///	���b�Z�[�W�f�[�^�𑗐M����	</summary>
		/// <param name="message">
		/// ���M���郁�b�Z�[�W	</param>
		void SendData(const char* message);
		
		/// <summary>
		///	�I�u�W�F�N�g�����b�N����Ă��邩����	</summary>
		/// <param name="objectName">
		///	���肷��I�u�W�F�N�g��	</param>
		/// <returns>
		///	���b�N����Ă�����true�A����Ă��Ȃ����false��Ԃ�	</returns>
		bool IsRockObject(const char* objectName);
};

