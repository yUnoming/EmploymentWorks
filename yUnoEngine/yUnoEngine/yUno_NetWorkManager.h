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
#include "Server.h"


// ������������������������������ //
// �@�@		 �}�N����`		�@�@  //
// ������������������������������ //

namespace yUno_SystemManager
{
	/// <summary>
	///	�l�b�g���[�N�̏������Ǘ�����N���X	</summary>
	class yUno_NetWorkManager
	{
		private:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			/// �T�[�o�[	</summary>
			static Server* m_Server;

		public:
			// ----- enums / �񋓌^ ----- //
			/// <summary>
			///	����M���郁�b�Z�[�W�̎��	</summary>
			enum MessageType
			{
				/// <summary>
				///	�R���|�[�l���g�̒l�X�V	</summary>
				UpdateComponentValue,
				/// <summary>
				///	�I�u�W�F�N�g���N���b�N���ꂽ	</summary>
				ClickedObject
			};

			// ----- functions / �֐� ----- //
			/// <summary>
			///	������	</summary>
			static void Init();
			/// <summary>
			/// �I��	</summary>
			static void UnInit();
			
			/// <summary>
			///	�T�[�o�[�����擾	</summary>
			/// <returns>
			/// �T�[�o�[����Ԃ�	</returns>
			static Server* GetServer() { return m_Server; };
	};
}

