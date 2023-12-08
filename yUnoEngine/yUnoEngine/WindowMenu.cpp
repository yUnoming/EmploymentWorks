// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "WindowMenu.h"

#include "yUno_NetWorkManager.h"
#include "SceneManager.h"
#include "Test.h"

void WindowMenu::Create()
{
    // ���������� ���j���[�̐ݒ�E�쐬 ���������� //
    HMENU hMenu = CreateMenu(); // ���j���[�쐬
    HMENU hSubMenu;


    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);

    // ===== �쐬�^�u�쐬 ===== //
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_Create;
    mii.dwTypeData = (LPWSTR)(L"�쐬");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_Create, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_CreateCube;
    mii.dwTypeData = (LPWSTR)(L"Cube");
    InsertMenuItem(hSubMenu, ID_CreateCube, FALSE, &mii);

    // ===== �T�[�o�[�^�u�쐬 ===== //
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_Server;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_Server, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_OpenServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[���J��");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_CloseServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[�����");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_LoginServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[�Ƀ��O�C��");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_LogoutServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[���烍�O�A�E�g");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    mii.wID = ID_SendMessage;
    mii.dwTypeData = (LPWSTR)(L"���b�Z�[�W�𑗂�");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    // �E�B���h�E�Ƀ��j���[��ǉ�
    SetMenu(Application::GetWindow(), hMenu);
}

void WindowMenu::Run(WORD menuID)
{
    switch (menuID)
    {
        // ===== �쐬�^�O�̏��� ===== //
        // Cube�쐬
        case WindowMenu::ID_CreateCube:
            PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Test>(1, "Cube");
            break;
        // ===== �T�[�o�[�^�O�̏��� ===== //
        // �T�[�o�[���J��
        case WindowMenu::ID_OpenServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->OpenServer();
            break;
        // �T�[�o�[�����
        case WindowMenu::ID_CloseServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->CloseServer();
            break;
        // �T�[�o�[�Ƀ��O�C��
        case WindowMenu::ID_LoginServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->LoginServer();
            break;
        // �T�[�o�[���烍�O�A�E�g
        case WindowMenu::ID_LogoutServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->LogoutServer();
            break;
        // ���b�Z�[�W�𑗂�
        case WindowMenu::ID_SendMessage:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData();
            break;
        // ��L�ȊO
        default:
            break;
    }
}
