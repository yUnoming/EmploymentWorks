// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "WindowMenu.h"
#include "Application.h"

void WindowMenu::Create()
{
    // ���������� ���j���[�̐ݒ�E�쐬 ���������� //
    HMENU hMenu = CreateMenu(); // ���j���[�쐬
    HMENU hSubMenu;


    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
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
