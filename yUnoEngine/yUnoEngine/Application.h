#pragma once
/**
* @file		Application.h
* @brief	Applicationクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.10.29
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <Windows.h>

/// <summary>
/// アプリケーション起動に必要な処理を行うクラス	</summary>
class Application
{
	private:
		// ----- variables / 変数 ----- //
		/// <summary>
		///	インスタンスハンドル	</summary>
		HINSTANCE		m_hInst;
		/// <summary>
		/// ウィンドウハンドル	</summary>
		static HWND     m_hWnd;
		/// <summary>
		/// ウィンドウの横幅	</summary>
		static UINT		m_wndWidth;
		/// <summary>
		///	ウィンドウの縦幅	</summary>
		static UINT		m_wndHeight;

		// ----- functions / 関数 ----- //
		/// <summary>
		/// アプリケーションの初期化	</summary>
		bool InitApp();
		/// <summary>
		///	アプリケーションの終了		</summary>
		void UnInitApp();
		/// <summary>
		///	ウィンドウの初期化			</summary>
		bool InitWnd();
		/// <summary>
		/// ウィンドウの終了			</summary>
		void UnInitWnd();
		/// <summary>
		///	メインループ				</summary>
		void MainLoop();

		/// <summary>
		/// ウィンドウズプロシージャ	</summary>
		/// <param name="hWnd">
		/// ウィンドウハンドル			</param>
		/// <param name="msg">
		/// メッセージ					</param>
		/// <param name="wp">
		/// メッセージ情報				</param>
		/// <param name="lp">
		/// メッセージ情報				</param>
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

	public:
		// ----- functions / 関数 ----- //
		/// <summary>
		/// アプリケーションの開始	</summary>
		void Run();

		/// <summary>
		/// ウィンドウハンドルを取得
		/// </summary>
		/// <returns>
		/// 現在のウィンドウハンドル</returns>
		static HWND GetWindow() { return m_hWnd; };

		/// <summary>
		/// ウィンドウの縦幅を取得		</summary>
		/// <returns>
		///	現在のウィンドウの縦幅		</returns>
		static UINT GetWindowWidth() { return m_wndWidth; };
		/// <summary>
		/// ウィンドウの横幅を取得		</summary>
		/// <returns>
		/// 現在のウィンドウの横幅		</returns>
		static UINT GetWindowHeight() { return m_wndHeight; };
};

