// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Application.h"
#include "WindowMenu.h"
#include "yUno_MainManager.h"
#include "yUno_KeyInputManager.h"
#include "yUno_MouseInputManager.h"

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　       マクロ宣言          //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// ----- ウィンドウ初期サイズ -----//
#define WINDOW_HEIGHT 540   // 縦幅
#define WINDOW_WIDTH  960    // 横幅

// ----- 命名 ----- //
// ウィンドウクラス名
#define WINDOWCLASS_NAME TEXT("Cubeor Shooter")
// ウィンドウ名
#define WINDOW_NAME TEXT("Cubeor Shooter")


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　       using宣言      　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace yUno_SystemManager;


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
HWND Application::m_hWnd;		// ウィンドウハンドル
UINT Application::m_wndWidth;	// ウィンドウの横幅
UINT Application::m_wndHeight;	// ウィンドウの縦幅


void Application::Run()
{
    // アプリケーションの初期化が正常に行われた？
    if (InitApp())
    {
        MainLoop(); // メインループ開始
    }

    // 終了処理
    UninitApp();
}

bool Application::InitApp()
{
    // ウィンドウの初期化が正常に行われた？
    if (InitWnd())
    {
        // 正常に行われたことを伝える
        return true;
    }

    // 正常に行われなかったことを伝える
    return false;
}

void Application::UninitApp()
{
    // ウィンドウの終了処理を行う
    UninitWnd();
}

bool Application::InitWnd()
{
    // ===== ウィンドウの設定・作成 ===== //
    // インスタンスハンドルを取得
    auto hInst = GetModuleHandle(nullptr);

    // ウィンドウの幅を設定
    m_wndWidth = WINDOW_WIDTH;     // 横幅
    m_wndHeight = WINDOW_HEIGHT;   // 縦幅

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
        return false;   // 正常に行えなかったことを伝える

    // インスタンスハンドルを代入
    m_hInst = hInst;

    // ウィンドウのサイズを設定
    RECT rc = {};
    rc.right = static_cast<LONG>(m_wndWidth);     // 横幅
    rc.bottom = static_cast<LONG>(m_wndHeight);   // 縦幅

    // ウィンドウサイズを調整
    auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    AdjustWindowRect(&rc, style, FALSE);

    // ウィンドウを作成
    m_hWnd = CreateWindowEx(
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
    if (m_hWnd == nullptr)
        return false;   // 正常に行えなかったことを伝える

    // ウィンドウを表示.
    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    // ウィンドウを更新.
    UpdateWindow(m_hWnd);

    // ウィンドウにフォーカスを設定.
    SetFocus(m_hWnd);

#if _DEBUG
    // ----- ウィンドウのメニュー作成 ----- //
    WindowMenu::Create();
#endif

    // 正常に行えたことを伝える
    return true;
}

void Application::UninitWnd()
{
    // ウィンドウの登録を解除.
    if (m_hInst != nullptr)
        UnregisterClass(WINDOWCLASS_NAME, m_hInst);

    m_hInst = nullptr;
    m_hWnd = nullptr;
}

void Application::MainLoop()
{
    // ===== 初期化処理 ===== //
    yUno_MainManager::Init(this);

    MSG msg = {};

    // ウィンドウが閉じられるまでループ
    while (WM_QUIT != msg.message)
    {
        // メッセージが更新された？
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) == TRUE)
        {
            DispatchMessage(&msg);  // メッセージの更新
            //TranslateMessage(&msg); // 文字入力を取得する場合はこの関数も必要
        }
        else
        {
            // ===== 更新処理 ====== //
            yUno_MainManager::Update();

            // ===== 描画処理 ===== //
            yUno_MainManager::Draw();
        }
    }

    // ===== 終了処理 ===== //
    yUno_MainManager::Uninit();
}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // ウィンドウを閉じるアクションが発生した場合
        case WM_CLOSE:
            // 終了確認で「OK」が押された？
            if (MessageBox(NULL, L"終了しますか？", L"終了確認", MB_OKCANCEL) == IDOK)
            {
                // ウィンドウを閉じる
                DestroyWindow(hWnd);
            }
            // 終了確認で「CANCEL」が押された
            else
            {
                // ウィンドウを閉じないために、WM_NULLを代入
                msg = WM_NULL;
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
            yUno_KeyInputManager::SetKeyDown(KeyID);
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
            yUno_KeyInputManager::SetKeyUp(KeyID);
            break;
        }
        // メニューバーがクリックされた場合
        case WM_COMMAND:
        {
            // クリックされた内容の実行処理
            WindowMenu::Run((LOWORD(wParam)));
            break;
        }

        // マウスの左ボタンが押された場合
        case WM_LBUTTONDOWN:
            // 左ボタンが押されたことを設定する関数を実行
            yUno_MouseInputManager::SetMouseDown(LeftButton);
            break;

        // マウスの左ボタンが離された場合
        case WM_LBUTTONUP:
            // 左ボタンが離されたことを設定する関数を実行
            yUno_MouseInputManager::SetMouseUp(LeftButton);
            break;

        // マウスのスクロールホイールボタンが押された場合
        case WM_MBUTTONDOWN:
            // スクロールホイールボタンが押されたことを設定する関数を実行
            yUno_MouseInputManager::SetMouseDown(ScrollWheelButton);
            break;

        // マウスのスクロールホイールボタンが離された場合
        case WM_MBUTTONUP:
            // スクロールホイールボタンが離されたことを設定する関数を実行
            yUno_MouseInputManager::SetMouseUp(ScrollWheelButton);
            break;

        // マウススクロールホイールボタンが回転した場合
        case WM_MOUSEWHEEL:
            yUno_MouseInputManager::SetMouseWheelState(HIWORD(wParam) % 120 / 16);
            break;

        // マウスの右ボタンが押された場合
        case WM_RBUTTONDOWN:
            // 右ボタンが押されたことを設定する関数を実行
            yUno_MouseInputManager::SetMouseDown(RightButton);
            break;

        // マウスの右ボタンが離された場合
        case WM_RBUTTONUP:
            // 右ボタンが離されたことを設定する関数を実行
            yUno_MouseInputManager::SetMouseUp(RightButton);
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
