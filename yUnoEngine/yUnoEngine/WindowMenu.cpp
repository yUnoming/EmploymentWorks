// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "WindowMenu.h"
#include "Application.h"

void WindowMenu::Create()
{
    // ＝＝＝＝＝ メニューの設定・作成 ＝＝＝＝＝ //
    HMENU hMenu = CreateMenu(); // メニュー作成
    HMENU hSubMenu;


    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_Server;
    mii.dwTypeData = (LPWSTR)(L"サーバー");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_Server, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_OpenServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーを開く");
    // 作成したメニューをアイテムとして追加
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_CloseServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーを閉じる");
    // 作成したメニューをアイテムとして追加
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_LoginServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーにログイン");
    // 作成したメニューをアイテムとして追加
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_LogoutServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーからログアウト");
    // 作成したメニューをアイテムとして追加
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_SendMessage;
    mii.dwTypeData = (LPWSTR)(L"メッセージを送る");
    // 作成したメニューをアイテムとして追加
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    // ウィンドウにメニューを追加
    SetMenu(Application::GetWindow(), hMenu);
}
