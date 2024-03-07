// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Application.h"
#include <time.h>

#if _DEBUG
// Debugビルド時のエントリポイント
int main()
{
    srand((unsigned int)time(NULL));    // 乱数用

    //**  アプリケーション実行  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
#else
// Releaseビルド時のエントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand((unsigned int)time(NULL));    // 乱数用

    //**  アプリケーション実行  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
#endif