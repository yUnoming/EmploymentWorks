#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <Windows.h>


class Application
{
	private:
		// ----- variables ----- //
		HINSTANCE   m_hInst;		// インスタンスハンドル
		HWND        m_hWnd;			// ウィンドウハンドル
		static UINT		m_Wnd_Width;	// ウィンドウの横幅
		static UINT		m_Wnd_Height;	// ウィンドウの縦幅

		// ----- methods ----- //
		bool InitApp();		// アプリケーションの初期化
		void UnInitApp();	// アプリケーションの終了
		bool InitWnd();		// ウィンドウの初期化
		void UnInitWnd();	// ウィンドウの終了
		void MainLoop();	// メインループ

		// ウィンドウズプロシージャ
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

	public:
		// ----- methods ----- //
		// アプリケーションの開始
		void Run();

		// ウィンドウハンドルを取得
		HWND Get_Window() { return m_hWnd; };

		// ウィンドウの縦幅を取得
		UINT Get_WindowWidth() { return m_Wnd_Width; };
		// ウィンドウの横幅を取得
		UINT Get_WindowHeight() { return m_Wnd_Height; };
};

