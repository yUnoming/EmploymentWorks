#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <Windows.h>


class Application
{
	private:
		// ----- variables ----- //
		HINSTANCE   m_hInst;		// �C���X�^���X�n���h��
		HWND        m_hWnd;			// �E�B���h�E�n���h��
		static UINT		m_Wnd_Width;	// �E�B���h�E�̉���
		static UINT		m_Wnd_Height;	// �E�B���h�E�̏c��

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
		// �A�v���P�[�V�����̊J�n
		void Run();

		// �E�B���h�E�n���h�����擾
		HWND Get_Window() { return m_hWnd; };

		// �E�B���h�E�̏c�����擾
		UINT Get_WindowWidth() { return m_Wnd_Width; };
		// �E�B���h�E�̉������擾
		UINT Get_WindowHeight() { return m_Wnd_Height; };
};

