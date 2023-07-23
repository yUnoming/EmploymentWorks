#pragma once

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <Windows.h>


class Application
{
	private:
		// ----- variables ----- //
		HINSTANCE   m_hInst;    // インスタンスハンドル
		HWND        m_hWnd;		// ウィンドウハンドル

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
		// アプリケーションを開始する関数
		void Run();

		// ウィンドウハンドルを返す
		HWND Get_Window() { return m_hWnd; };
};

