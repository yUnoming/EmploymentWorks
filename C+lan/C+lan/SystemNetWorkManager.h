#pragma once
/**
* @file		SystemNetWorkManager.h
* @brief	SystemNetWorkManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.16
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Server.h"


namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			///	�l�b�g���[�N�̏������Ǘ�����N���X	</summary>
			class SystemNetWorkManager
			{
				private:
					// ----- variables / �ϐ� ----- //
					/// <summary>
					/// �T�[�o�[	</summary>
					static Server* m_Server;

				public:
					// ----- functions / �֐� ----- //
					/// <summary>
					///	������	</summary>
					static void Init();
					/// <summary>
					/// �I��	</summary>
					static void Uninit();

					/// <summary>
					///	�T�[�o�[�����擾	</summary>
					/// <returns>
					/// �T�[�o�[����Ԃ�	</returns>
					static Server* GetServer() { return m_Server; };
			};
		}
	}
}

