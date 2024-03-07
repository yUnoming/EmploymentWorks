// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Application.h"
#include <time.h>

#if _DEBUG
int main()
{
    srand((unsigned int)time(NULL));    // 乱数用

    //**  アプリケーション実行  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    srand((unsigned int)time(NULL));    // 乱数用

    //**  アプリケーション実行  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
#endif