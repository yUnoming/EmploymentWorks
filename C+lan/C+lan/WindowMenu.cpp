// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemNetWorkManager.h"
#include "SystemSceneManager.h"

#include "WindowMenu.h"
#include "SceneManager.h"

#include "TemplateCube.h"
#include "TemplateText.h"

void Ctlan::PrivateSystem::ApplicationSystem::WindowMenu::Create()
{
    // ＝＝＝＝＝ メニューの設定・作成 ＝＝＝＝＝ //
    HMENU hMenu = CreateMenu(); // メニュー作成
    HMENU hSubMenu;

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);

    // ===== ファイルタブ作成 ===== //
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_File;
    mii.dwTypeData = (LPWSTR)(L"ファイル");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_File, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_NewScene;
    mii.dwTypeData = (LPWSTR)(L"新規シーン");
    InsertMenuItem(hSubMenu, ID_NewScene, FALSE, &mii);

    mii.wID = ID_OpenScene;
    mii.dwTypeData = (LPWSTR)(L"シーンを開く");
    InsertMenuItem(hSubMenu, ID_OpenScene, FALSE, &mii);

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
    mii.wID = ID_CreateText;
    mii.dwTypeData = (LPWSTR)(L"Text");
    InsertMenuItem(hSubMenu, ID_CreateText, FALSE, &mii);

    // ===== サーバータブ作成 ===== //
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_Server;
    mii.dwTypeData = (LPWSTR)(L"サーバー");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_Server, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_OpenServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーを開く");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);
    mii.wID = ID_CloseServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーを閉じる");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);
    mii.wID = ID_LoginServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーにログイン");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);
    mii.wID = ID_LogoutServer;
    mii.dwTypeData = (LPWSTR)(L"サーバーからログアウト");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    // ウィンドウにメニューを追加
    SetMenu(Application::GetWindow(), hMenu);
}

void Ctlan::PrivateSystem::ApplicationSystem::WindowMenu::Run(WORD menuID)
{
    switch (menuID)
    {
        // ===== ファイルタブの処理 ===== //
        //------------//
        // 新規シーン //
        case WindowMenu::ID_NewScene:
        {
            // シーン名入力
            char sceneName[30];
            printf("\nシーン名を入力してください（アルファベットのみ）\n");
            rewind(stdin);
            int r = scanf_s("%[^\n]", sceneName, 30);	// 改行以外を読み込む

            // 新規シーン作成
            SystemManager::SystemSceneManager::CreateNewScene(sceneName);
            break;
        }
        //--------------//
        // シーンを開く //
        case WindowMenu::ID_OpenScene:
        {
            // シーン名入力
            char sceneName[30];
            printf("\nシーン名を入力してください（アルファベットのみ）\n");
            rewind(stdin);
            int r = scanf_s("%[^\n]", sceneName, 30);	// 改行以外を読み込む
            SceneManager::LoadScene(sceneName);
            break;
        }
        // ===== 作成タブの処理 ===== //
        //----------//
        // Cube作成 //
        case WindowMenu::ID_CreateCube:
        {
            // 新たにキューブを作成し、そのオブジェクト情報を取得
            GameObject* cubeObject = Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateCube>(1, "Cube");

            // メッセージデータ作成
            MessageData messageData;
            messageData.message.header.type = MessageType::CreateCube;
            messageData.message.bodyObject.transform.position = cubeObject->transform->position;
            // メッセージを送る処理を実行
            SystemManager::SystemNetWorkManager::GetServer()->SendMessageData(messageData);
            break;
        }
        //----------//
        // Text作成 //
        case WindowMenu::ID_CreateText:
        {
            // 新たにテキストを作成
            Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateText>(3, "Text");

            // メッセージデータ作成
            MessageData messageData;
            messageData.message.header.type = MessageType::CreateText;
            // メッセージを送る処理を実行
            SystemManager::SystemNetWorkManager::GetServer()->SendMessageData(messageData);
            break;
        }
        // ===== サーバータブの処理 ===== //
        //----------------//
        // サーバーを開く //
        case WindowMenu::ID_OpenServer:
            SystemManager::SystemNetWorkManager::GetServer()->OpenServer();
            break;
        //------------------//
        // サーバーを閉じる //
        case WindowMenu::ID_CloseServer:
            SystemManager::SystemNetWorkManager::GetServer()->CloseServer();
            break;
        //--------------------//
        // サーバーにログイン //
        case WindowMenu::ID_LoginServer:
            SystemManager::SystemNetWorkManager::GetServer()->LoginServer();
            break;
        //------------------------//
        // サーバーからログアウト //
        case WindowMenu::ID_LogoutServer:
            SystemManager::SystemNetWorkManager::GetServer()->LogoutServer();
            break;
        //----------//
        // 上記以外 //
        default:
            break;
    }
}
