#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_SceneManager.h"

class yUno_MainManager
{
	private:
		// ----- variables / �ϐ� ----- //
		// ���݂̃V�[��
		static yUno_SceneManager* m_NowScene;

		// �f���v���C�����ǂ���
		static bool m_DemoPlay;

	public:
		// ----- methods / �֐� ----- //
		static void Init(Application* app);
		static void UnInit();
		static void Update();
		static void Draw();
};
