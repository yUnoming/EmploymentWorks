#pragma once

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <Windows.h>


class Application
{
	private:
		// ----- variables ----- //
		HINSTANCE   m_hInst;    // �C���X�^���X�n���h��
		HWND        m_hWnd;		// �E�B���h�E�n���h��

		// ----- methods ----- //
		bool InitApp();		// �A�v���P�[�V�����̏�����
		void UnInitApp();	// �A�v���P�[�V�����̏I��
		bool InitWnd();		// �E�B���h�E�̏�����
		void UnInitWnd();	// �E�B���h�E�̏I��
		void MainLoop();	// ���C�����[�v

		// �E�B���h�E�Y�v���V�[�W��
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

	public:
		// ----- methods ----- //
		// �A�v���P�[�V�������J�n����֐�
		void Run();

		// �E�B���h�E�n���h����Ԃ�
		HWND Get_Window() { return m_hWnd; };
};

