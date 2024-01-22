#pragma once
/**
* @file		LaunchSceneInformation.h
* @brief	LaunchSceneInformation�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2024.01.06
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace Information
		{
			/// <summary>
			/// �N������V�[�����</summary>
			class LaunchSceneInformation
			{
				private:
					// ----- variables / �ϐ� ----- //
					/// <summary>
					///	�N������V�[����	</summary>
					char m_launchSceneName[30];

				public:
					// ----- functions / �֐� ----- //
					/// <summary>
					///	�R���X�g���N�^	</summary>
					LaunchSceneInformation();
					/// <summary>
					///	���̃��[�h	</summary>
					void Load();
					/// <summary>
					///	���̃Z�[�u	</summary>
					void Save();

					/// <summary>
					///	�N������V�[�������擾	</summary>
					/// <returns>
					///	�V�[��������΋N������V�[�����A�������nullptr	</returns>
					const char* GetLaunchSceneName();
			};
		}
	}
}

