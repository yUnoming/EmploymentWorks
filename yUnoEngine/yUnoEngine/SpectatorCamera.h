#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"


// ������������������������������������ //
//										//
// �@�@�G���W�����Ŏg�p�����J�����@�@ //
//										//
// ������������������������������������ //
class SpectatorCamera : public GameObject
{
	private:
		// ----- variables / �ϐ� ----- //
		///<summary>
		///�N���b�N���ꂽ�I�u�W�F�N�g��������ϐ�	</summary>
		GameObject* m_Clicked_Object = nullptr;

	public:
		void Init();
		void Update();
};
