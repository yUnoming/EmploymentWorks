// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Application.h"


int main()
{

    // ���������� ���j���[�̐ݒ�E�쐬 ���������� //
    //HMENU hMenu = CreateMenu(); // ���j���[�쐬
    //const UINT ID_MENU_1 = 1;
    //const UINT ID_MENU_2 = 2;

    //MENUITEMINFO mii;
    //memset(&mii, 0, sizeof(MENUITEMINFO));
    //mii.cbSize = sizeof(MENUITEMINFO);

    //mii.fMask = MIIM_ID | MIIM_STRING;
    //mii.wID = ID_MENU_1;
    //mii.dwTypeData = (LPWSTR)(_T("���j���[�P"));

    //// �쐬�������j���[�ɃA�C�e���ǉ�
    //InsertMenuItem(hMenu, ID_MENU_1, FALSE, &mii);

    //mii.wID = ID_MENU_2;
    //mii.dwTypeData = (LPWSTR)(_T("���j���[�Q"));

    //InsertMenuItem(hMenu, ID_MENU_2, FALSE, &mii);

    // �E�B���h�E�Ƀ��j���[��ǉ�
    //SetMenu(hWnd, hMenu);


    // �A�v���P�[�V�������s
    Application app;
    app.Run();

    return 0;
}
