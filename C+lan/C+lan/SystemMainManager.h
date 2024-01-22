#pragma once
/**
* @file		SystemMainManager.h
* @brief	SystemMainManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SystemSceneManager.h"

namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			/// ���C���ŃV�X�e�����񂷂��߂̃N���X	</summary>
			class SystemMainManager
			{
				private:
					// ----- variables / �ϐ� ----- //
					/// <summary>
					/// ���݂̃v���C���	</summary>
					static bool m_demoPlay;

				public:
					// ----- functions / �֐� ----- //
					/// <summary>
					/// ������	</summary>
					/// <param name="app">
					/// �A�v���P�[�V�������	</param>
					static void Init(Application* app);
					/// <summary>
					/// �I��	</summary>
					static void Uninit();
					/// <summary>
					///	�X�V	</summary>
					static void Update();
					/// <summary>
					/// �`��	</summary>
					static void Draw();
			};
		}
	}
}
