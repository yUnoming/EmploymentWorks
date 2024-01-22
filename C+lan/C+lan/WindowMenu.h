#pragma once
/**
* @file		WindowMenu.h
* @brief	WindowMenu�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.28
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Application.h"


namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace ApplicationSystem
		{
			/// <summary>
			///	�E�B���h�E�㕔�ɂ��郁�j���[�������N���X	</summary>
			class WindowMenu
			{
				public:
					// ----- enum / �񋓌^ ----- //
					/// <summary>
					///	�e���j���[�Ɋ���U��ID	</summary>
					enum MenuID
					{
						// �t�@�C���^�u
						ID_File,
						ID_NewScene,
						ID_OpenScene,

						// �쐬�^�u
						ID_Create = 10,
						ID_CreateCube,
						ID_CreateText,

						// �T�[�o�[�^�u
						ID_Server = 20,
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
		}
	}
}