#pragma once
/**
* @file		WindowMenu.h
* @brief	WindowMenu�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.28
*/

class WindowMenu
{
	public:
		// ----- enum / �񋓌^ ----- //
		/// <summary>
		///	�e���j���[�Ɋ���U��ID	</summary>
		enum MenuID
		{
			ID_Server = 1,
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
};

