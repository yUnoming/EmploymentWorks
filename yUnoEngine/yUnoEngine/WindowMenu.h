#pragma once
/**
* @file		WindowMenu.h
* @brief	WindowMenu�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.28
*/

#include "Application.h"

class WindowMenu
{
	public:
		// ----- enum / �񋓌^ ----- //
		/// <summary>
		///	�e���j���[�Ɋ���U��ID	</summary>
		enum MenuID
		{
			// �쐬�^�u
			ID_Create = 1,
			ID_CreateCube,

			// �T�[�o�[�^�u
			ID_Server = 10,
			ID_OpenServer,
			ID_CloseServer,
			ID_LoginServer,
			ID_LogoutServer,
			ID_SendMessage,
		};

		// ----- functions / �֐� ----- //
		/// <summary>
		///	���j���[���쐬����	</summary>
		static void Create();

		/// <summary>
		///	���j���[���e�ɏ]���āA���������s	</summary>
		static void Run(WORD menuID);
};
