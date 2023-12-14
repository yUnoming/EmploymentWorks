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
#include "Message.h"


/// <summary>
///	�T�[�o�[���������߂̃N���X	</summary>
class Server
{
	private:
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
		// ----- structs / �\���� ----- //
		/// <summary>
		///	�ʐM���[�U�[���	</summary>
		struct CommunicationUserData
		{
			/// <summary>
			///	���[�U�[�����N	</summary>
			ServerRank userRank;
			/// <summary>
			///	���[�U�[�A�h���X	</summary>
			sockaddr_in address;
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
		sockaddr_in m_receiveAddress{};
		/// <summary>
		///	���M�f�[�^	</summary>
		MessageData m_sendData;
		/// <summary>
		///	��M�f�[�^	</summary>
		MessageData m_receiveData;
		
		/// <summary>
		///	��M�X���b�h	</summary>
		std::thread m_receiveThread;
		/// <summary>
		///	��M�J�n�p�X���b�h	</summary>
		std::thread m_comStartThread;

		/// <summary>
		/// �f�[�^�̒ʐM��� </summary>
		bool m_isCommunicationData;
		/// <summary>
		///	�ʐM�J�n�̍Œ����ǂ���	</summary>
		bool m_isCommunicationDuring;

		/// <summary>
		///	���g�̃T�[�o�[�ł̒n��	</summary>
		ServerRank m_myServerRank;

		// ���b�N���Ă���I�u�W�F�N�g��
		char rockObjectName[30];

		/// <summary>
		///	�ʐM���[�U�[���X�g	</summary>
		std::list<CommunicationUserData> m_comUserList;

		// ----- functions / �֐� ----- //
		/// <summary>
		/// ��M�X���b�h	</summary>
		void ReceiveThread();
		/// <summary>
		///	��M�J�n�X���b�h	</summary>
		void CommunicationStartThread();

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
		void SendMessageData(MessageData& messageData);
		


		/// <summary>
		///	�I�u�W�F�N�g�����b�N����Ă��邩����	</summary>
		/// <param name="objectName">
		///	���肷��I�u�W�F�N�g��	</param>
		/// <returns>
		///	���b�N����Ă�����true�A����Ă��Ȃ����false��Ԃ�	</returns>
		bool IsRockObject(const char* objectName);
};

