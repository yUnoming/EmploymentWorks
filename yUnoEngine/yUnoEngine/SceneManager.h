#pragma once
/**
* @file		SceneManager.h
* @brief	SceneManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_SceneManager.h"


namespace PublicSystem
{
	/// <summary>
	/// �V�[���Ɋւ���@�\���܂Ƃ߂��N���X	</summary>
	class SceneManager : private yUno_SceneManager
	{
		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			/// ���݊J���Ă���V�[�����̃I�u�W�F�N�g��S�ĕԂ�	</summary>
			/// <returns>
			/// ���݃V�[���̑S�I�u�W�F�N�g</returns>
			std::array<std::list<GameObject*>, 4> static GetSceneObjectAll();
			
			/// <summary>
			///	���݊J���Ă���V�[�����擾	</summary>
			/// <returns>
			///	���݃V�[���̃|�C���^�[	</returns>
			static SceneBase* GetNowScene();
	};
};

