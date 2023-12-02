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
			ID_Server,
			ID_OpenServer = 1,
			ID_CloseServer = 2,
			ID_LoginServer = 3,
			ID_LogoutServer = 4,
			ID_SendMessage = 5,
		};

		// ----- functions / �֐� ----- //
		/// <summary>
		///	���j���[���쐬����	</summary>
		static void Create();
};

