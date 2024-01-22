// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Application.h"
#include <time.h>

int main()
{
    srand((unsigned int)time(NULL));    // 乱数用

    //**  アプリケーション実行  **//
    Ctlan::PrivateSystem::Application app;
    app.Run();

    return 0;
}
