// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <Windows.h>
#include <iostream>  // cin, coutを使用するため
#include <tchar.h>   // _Tを使用するため

#include "yUno_KeyInputManager.h"
#include "yUno_TimeManager.h"

#include "KeyInput.h"
#include "Time.h"

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　      using宣言 　         //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace yUno_SystemManager;
using namespace System;

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   プロトタイプ宣言        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// ウィンドウズプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　       マクロ宣言          //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// ウィンドウサイズ
#define WINDOW_HEIGHT 540   // 縦幅
#define WINDOW_WIDTH 960    // 横幅

// 命名
#define WINDOWCLASS_NAME _T("ウィンドウクラス名")   // ウィンドウクラス名（起動時、画面下のアイコンにカーソルを合わせた時）
#define WINDOW_NAME _T("ウィンドウ名")              // ウィンドウ名（起動時、スクリーン上）

int main()
{
    // ＝＝＝＝＝ ウィンドウの設定・作成 ＝＝＝＝＝ //
    // インスタンスハンドルを取得
    auto hInst = GetModuleHandle(nullptr);

    // ウィンドウの設定
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);                         // サイズ（バイト単位）
    wc.style = CS_HREDRAW | CS_VREDRAW;                     // スタイル
    wc.lpfnWndProc = WndProc;                               // ウィンドウプロシージャへのポインター
    wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);            // クラスアイコンへのハンドル
    wc.hCursor = LoadCursor(hInst, IDC_HELP);               // クラスカーソルへのハンドル
    wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);  // クラスの背景ブラシへのハンドル
    wc.lpszMenuName = nullptr;                              // クラスメニューのリソース名を指定するnullで終わる文字列へのポインター
    wc.lpszClassName = WINDOWCLASS_NAME;                   // ウィンドウクラス名
    wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);          // ウィンドウクラスに関連付けられている小さなアイコンへのハンドル

    // ウィンドウの登録
    if (!RegisterClassEx(&wc))
    {
        // ウィンドウクラスの登録が正しく行えなかった場合
        return false;
    }

    // ウィンドウのサイズを設定
    RECT rc = {};
    rc.right = static_cast<LONG>(WINDOW_WIDTH);     // 横幅
    rc.bottom = static_cast<LONG>(WINDOW_HEIGHT);   // 縦幅

    // ウィンドウサイズを調整
    auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    AdjustWindowRect(&rc, style, FALSE);

    // ウィンドウを作成
    HWND hWnd = CreateWindowEx(
        0,                          // 拡張ウィンドウスタイル
        WINDOWCLASS_NAME,           // ウィンドウクラス名
        WINDOW_NAME,                // ウィンドウ名
        style,                      // ウィンドウスタイル
        CW_USEDEFAULT,              // ウィンドウ左の座標値
        CW_USEDEFAULT,              // ウィンドウ上の座標値
        rc.right - rc.left,         // ウィンドウの幅         
        rc.bottom - rc.top,         // ウィンドウの高さ
        nullptr,                    // 作成されるウィンドウの親ウィンドウ or 所有者ウィンドウへのハンドル
        nullptr,                    // メニューへのハンドル
        hInst,                      // インスタンスへのハンドル
        nullptr);                   // ウィンドウに渡される値へのポインター

    // ウィンドウが作成出来なかった？
    if (hWnd == nullptr)
    {
        return false;
    }

    // ＝＝＝＝＝ メニューの設定・作成 ＝＝＝＝＝ //
    //HMENU hMenu = CreateMenu(); // メニュー作成
    //const UINT ID_MENU_1 = 1;
    //const UINT ID_MENU_2 = 2;

    //MENUITEMINFO mii;
    //memset(&mii, 0, sizeof(MENUITEMINFO));
    //mii.cbSize = sizeof(MENUITEMINFO);

    //mii.fMask = MIIM_ID | MIIM_STRING;
    //mii.wID = ID_MENU_1;
    //mii.dwTypeData = (LPWSTR)(_T("メニュー１"));

    //// 作成したメニューにアイテム追加
    //InsertMenuItem(hMenu, ID_MENU_1, FALSE, &mii);

    //mii.wID = ID_MENU_2;
    //mii.dwTypeData = (LPWSTR)(_T("メニュー２"));

    //InsertMenuItem(hMenu, ID_MENU_2, FALSE, &mii);

    // ウィンドウにメニューを追加
    //SetMenu(hWnd, hMenu);

    // ウィンドウを表示.
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // ウィンドウを更新.
    UpdateWindow(hWnd);

    // ウィンドウにフォーカスを設定.
    SetFocus(hWnd);

    // ＝＝＝＝＝ システムの初期化処理 ＝＝＝＝＝ //
    // 時間
    yUno_TimeManager::Init();

    // ＝＝＝＝＝ メインループ ＝＝＝＝＝ //
    MSG msg = {};

    // ウィンドウが閉じられるまでループ
    while (WM_QUIT != msg.message)
    {
        // メッセージが更新された？
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) == true)
        {
            DispatchMessage(&msg);  // メッセージの更新
            //TranslateMessage(&msg); // 文字入力を取得する場合はこの関数も必要
        }
        else
        {
            // ＝＝＝＝＝ システムの更新処理 ＝＝＝＝＝ //
            // 時間
            yUno_TimeManager::Update();
           
            // キー入力
            yUno_KeyInputManager::Update();
            
            // ＝＝＝＝＝ ゲーム内処理 ＝＝＝＝＝ //
            // KeyInputのテスト：LShiftが押された？
            if (KeyInput::GetKeyDown_Trigger(KeyName::LeftShift))
            {
                std::cout << "Pushed LShift" << std::endl;
            }

            // KeyInputのテスト：RShiftが押された？
            if (KeyInput::GetKeyDown_Trigger(KeyName::RightShift))
            {
                std::cout << "Pushed RShift" << std::endl;
            }

            // 現在のキー入力状態を保存する
            yUno_KeyInputManager::Keep_Now_KeyInfo();
        }
    }

    return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    // ウィンドウを閉じるアクションが発生した場合
    case WM_CLOSE:
        // 終了確認で「OK」が押された？
        if (MessageBox(NULL, _T("終了しますか？"), _T("終了確認"), MB_OKCANCEL) == IDOK)
        {
            // ウィンドウを閉じる
            DestroyWindow(hWnd);
        }
        break;

    // ウィンドウが閉じた場合
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    // キーが押された場合
    case WM_KEYDOWN:
    {
        // 押されているキーを取得
        WORD KeyID = HIWORD(lParam);

        // 求めた値が大きすぎる
        if (KeyID > 10000)
            KeyID -= 49152;  // 欲しい値に修正する
        // 求めた値がまだ大きすぎる
        if (KeyID > 10000)
            KeyID -= 32768;  // 欲しい値にさらに修正する

        // 押されたキーを保存する関数を実行
        yUno_KeyInputManager::Set_KeyDown(KeyID);
        break;
    }

    // キーが離された場合
    case WM_KEYUP:
    {
        // 押されているキーを取得
        WORD KeyID = HIWORD(lParam);

        // 求めた値が大きすぎる
        if (KeyID > 10000)
            KeyID -= 49152;  // 欲しい値に修正する
        // 求めた値がまだ大きすぎる
        if (KeyID > 10000)
            KeyID -= 32768;  // 欲しい値にさらに修正する

        // 離されたキーを保存する関数を実行
        yUno_KeyInputManager::Set_KeyUp(KeyID);
        break;
    }

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}
