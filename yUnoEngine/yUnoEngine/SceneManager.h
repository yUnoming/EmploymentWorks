#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_SceneManager.h"


namespace PublicSystem
{
	/// <summary>
	/// �V�[���Ɋւ��鑀����s����N���X
	/// </summary>
	class SceneManager : private yUno_SceneManager
	{
		public:

			// ----- functions / �֐� ----- //
			/// <summary>
			/// ���݊J���Ă���V�[�����̃I�u�W�F�N�g��S�ĕԂ�
			/// </summary>
			/// <returns>���݃V�[���̑S�I�u�W�F�N�g</returns>
			std::array<std::list<GameObject*>, 4> static GetSceneObjectAll();
	};
};

