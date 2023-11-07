#pragma once
/**
* @file		Application.h
* @brief	Application�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <Windows.h>

/// <summary>
/// �A�v���P�[�V�����N���ɕK�v�ȏ������s���N���X	</summary>
class Application
{
	private:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		///	�C���X�^���X�n���h��	</summary>
		HINSTANCE		m_hInst;
		/// <summary>
		/// �E�B���h�E�n���h��	</summary>
		static HWND     m_hWnd;
		/// <summary>
		/// �E�B���h�E�̉���	</summary>
		static UINT		m_wndWidth;
		/// <summary>
		///	�E�B���h�E�̏c��	</summary>
		static UINT		m_wndHeight;

		// ----- functions / �֐� ----- //
		/// <summary>
		/// �A�v���P�[�V�����̏�����	</summary>
		bool InitApp();
		/// <summary>
		///	�A�v���P�[�V�����̏I��		</summary>
		void UnInitApp();
		/// <summary>
		///	�E�B���h�E�̏�����			</summary>
		bool InitWnd();
		/// <summary>
		/// �E�B���h�E�̏I��			</summary>
		void UnInitWnd();
		/// <summary>
		///	���C�����[�v				</summary>
		void MainLoop();

		/// <summary>
		/// �E�B���h�E�Y�v���V�[�W��	</summary>
		/// <param name="hWnd">
		/// �E�B���h�E�n���h��			</param>
		/// <param name="msg">
		/// ���b�Z�[�W					</param>
		/// <param name="wp">
		/// ���b�Z�[�W���				</param>
		/// <param name="lp">
		/// ���b�Z�[�W���				</param>
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

	public:
		// ----- functions / �֐� ----- //
		/// <summary>
		/// �A�v���P�[�V�����̊J�n	</summary>
		void Run();

		/// <summary>
		/// �E�B���h�E�n���h�����擾
		/// </summary>
		/// <returns>
		/// ���݂̃E�B���h�E�n���h��</returns>
		static HWND GetWindow() { return m_hWnd; };

		/// <summary>
		/// �E�B���h�E�̏c�����擾		</summary>
		/// <returns>
		///	���݂̃E�B���h�E�̏c��		</returns>
		static UINT GetWindowWidth() { return m_wndWidth; };
		/// <summary>
		/// �E�B���h�E�̉������擾		</summary>
		/// <returns>
		/// ���݂̃E�B���h�E�̉���		</returns>
		static UINT GetWindowHeight() { return m_wndHeight; };
};

