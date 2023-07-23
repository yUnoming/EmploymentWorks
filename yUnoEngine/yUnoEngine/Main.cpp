// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Application.h"


int main()
{

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


    // アプリケーション実行
    Application app;
    app.Run();

    return 0;
}
