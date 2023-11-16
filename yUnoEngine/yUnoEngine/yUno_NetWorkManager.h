#pragma once
/**
* @file		Component.h
* @brief	Component�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <WinSock2.h>
#include <thread>

namespace yUno_SystemManager
{
	/// <summary>
	///	�l�b�g���[�N�̏������Ǘ�����N���X	</summary>
	class yUno_NetWorkManager
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
			/// �ʐM�J�n���Ă��邩�ǂ���	</summary>
			bool isCommunication;
			/// <summary>
			/// ��M�҂���Ԃ��ǂ��� </summary>
			bool isReceiveWaiting;


			// ----- functions / �֐� ----- //
			/// <summary>
			/// ��M�X���b�h	</summary>
			void ReceiveThread();

		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			///	�l�b�g���[�N�ʐM���J�n	</summary>
			int Start();
			/// <summary>
			///	�l�b�g���[�N�ʐM���I��	</summary>
			int End();
	};
}

