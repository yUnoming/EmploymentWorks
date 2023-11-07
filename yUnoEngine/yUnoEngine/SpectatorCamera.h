#pragma once
/**
* @file		SpectatorCamera.h
* @brief	SpectatorCamera�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "GameObject.h"


/// <summary>
///	�G���W�����Ŏg���J�����I�u�W�F�N�g	</summary>
class SpectatorCamera : public GameObject
{
	private:
		// ----- variables / �ϐ� ----- //
		///<summary>
		///�N���b�N���ꂽ�I�u�W�F�N�g��������ϐ�	</summary>
		GameObject* m_clickedObject = nullptr;

	public:
		void Init();
		void Update();
};

