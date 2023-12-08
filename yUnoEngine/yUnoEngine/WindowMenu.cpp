// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "WindowMenu.h"

#include "yUno_NetWorkManager.h"
#include "SceneManager.h"
#include "Test.h"

void WindowMenu::Create()
{
    // ＝＝＝＝＝ メニューの設定・作成 ＝＝＝＝＝ //
    HMENU hMenu = CreateMenu(); // メニュー作成
    HMENU hSubMenu;


    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);

    // ===== 作成タブ作成 ===== //
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_Create;
    mii.dwTypeData = (LPWSTR)(L"作成");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_Create, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_CreateCube;
    mii.dwTypeData = (LPWSTR)(L"Cube");
    InsertMenuItem(hSubMenu, ID_CreateCube, FALSE, &mii);

    // ===== サーバータブ作成 ===== //
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

void WindowMenu::Run(WORD menuID)
{
    switch (menuID)
    {
        // ===== 作成タグの処理 ===== //
        // Cube作成
        case WindowMenu::ID_CreateCube:
            PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Test>(1, "Cube");
            break;
        // ===== サーバータグの処理 ===== //
        // サーバーを開く
        case WindowMenu::ID_OpenServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->OpenServer();
            break;
        // サーバーを閉じる
        case WindowMenu::ID_CloseServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->CloseServer();
            break;
        // サーバーにログイン
        case WindowMenu::ID_LoginServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->LoginServer();
            break;
        // サーバーからログアウト
        case WindowMenu::ID_LogoutServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->LogoutServer();
            break;
        // メッセージを送る
        case WindowMenu::ID_SendMessage:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData();
            break;
        // 上記以外
        default:
            break;
    }
}
