// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "yUno_SceneManager.h"

#include "WindowMenu.h"
#include "SceneManager.h"

#include "TemplateCube.h"
#include "TemplateText.h"

void WindowMenu::Create()
{
    // ���������� ���j���[�̐ݒ�E�쐬 ���������� //
    HMENU hMenu = CreateMenu(); // ���j���[�쐬
    HMENU hSubMenu;

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);

    // ===== �t�@�C���^�u�쐬 ===== //
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_File;
    mii.dwTypeData = (LPWSTR)(L"�t�@�C��");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_File, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_NewScene;
    mii.dwTypeData = (LPWSTR)(L"�V�K�V�[��");
    InsertMenuItem(hSubMenu, ID_NewScene, FALSE, &mii);

    mii.wID = ID_OpenScene;
    mii.dwTypeData = (LPWSTR)(L"�V�[�����J��");
    InsertMenuItem(hSubMenu, ID_OpenScene, FALSE, &mii);

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
    mii.wID = ID_CreateText;
    mii.dwTypeData = (LPWSTR)(L"Text");
    InsertMenuItem(hSubMenu, ID_CreateText, FALSE, &mii);

    // ===== �T�[�o�[�^�u�쐬 ===== //
    mii.fMask = MIIM_ID | MIIM_STRING | MIIM_SUBMENU;
    mii.wID = ID_Server;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[");
    hSubMenu = mii.hSubMenu = CreatePopupMenu();
    InsertMenuItem(hMenu, ID_Server, TRUE, &mii);

    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_OpenServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[���J��");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);
    mii.wID = ID_CloseServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[�����");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);
    mii.wID = ID_LoginServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[�Ƀ��O�C��");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);
    mii.wID = ID_LogoutServer;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[���烍�O�A�E�g");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);
    mii.wID = ID_SendMessage;
    mii.dwTypeData = (LPWSTR)(L"���b�Z�[�W�𑗂�");
    InsertMenuItem(hSubMenu, ID_Server, FALSE, &mii);

    // �E�B���h�E�Ƀ��j���[��ǉ�
    SetMenu(Application::GetWindow(), hMenu);
}

void WindowMenu::Run(WORD menuID)
{
    switch (menuID)
    {
        // ===== �t�@�C���^�u�̏��� ===== //
        //------------//
        // �V�K�V�[�� //
        case WindowMenu::ID_NewScene:
        {
            // �V�[��������
            char sceneName[30];
            printf("\n�V�[��������͂��Ă��������i�A���t�@�x�b�g�̂݁j\n");
            rewind(stdin);
            int r = scanf_s("%[^\n]", sceneName, 30);	// ���s�ȊO��ǂݍ���

            // �V�K�V�[���쐬
            yUno_SceneManager::CreateNewScene(sceneName);
            break;
        }
        //--------------//
        // �V�[�����J�� //
        case WindowMenu::ID_OpenScene:
        {
            // �V�[��������
            char sceneName[30];
            printf("\n�V�[��������͂��Ă��������i�A���t�@�x�b�g�̂݁j\n");
            rewind(stdin);
            int r = scanf_s("%[^\n]", sceneName, 30);	// ���s�ȊO��ǂݍ���

            // �V�[�������[�h�o���Ȃ������H
            if (!SceneManager::LoadScene(sceneName))
            {
                // �V�X�e���ʒm��\��
                MessageBoxW(NULL, L"�V�[�������݂��܂���ł���", L"�G���[���b�Z�[�W", MB_OK);
            }
            break;
        }
        // ===== �쐬�^�u�̏��� ===== //
        //----------//
        // Cube�쐬 //
        case WindowMenu::ID_CreateCube:
        {
            // �V���ɃL���[�u���쐬���A���̃I�u�W�F�N�g�����擾
            GameObject* cubeObject = PublicSystem::SceneManager::GetNowScene()->AddSceneObject<EngineObject::TemplateCube>(1, "Cube");

            // ���b�Z�[�W�f�[�^�쐬
            MessageData messageData;
            messageData.message.header.type = MessageType::CreateCube;
            messageData.message.body.transform.position = cubeObject->transform->position;
            // ���b�Z�[�W�𑗂鏈�������s
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendMessageData(messageData);
            break;
        }
        //----------//
        // Text�쐬 //
        case WindowMenu::ID_CreateText:
        {
            // �V���Ƀe�L�X�g���쐬
            PublicSystem::SceneManager::GetNowScene()->AddSceneObject<EngineObject::TemplateText>(3, "Text");

            // ���b�Z�[�W�f�[�^�쐬
            MessageData messageData;
            messageData.message.header.type = MessageType::CreateText;
            // ���b�Z�[�W�𑗂鏈�������s
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendMessageData(messageData);
            break;
        }
        // ===== �T�[�o�[�^�u�̏��� ===== //
        //----------------//
        // �T�[�o�[���J�� //
        case WindowMenu::ID_OpenServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->OpenServer();
            break;
        //------------------//
        // �T�[�o�[����� //
        case WindowMenu::ID_CloseServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->CloseServer();
            break;
        //--------------------//
        // �T�[�o�[�Ƀ��O�C�� //
        case WindowMenu::ID_LoginServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->LoginServer();
            break;
        //------------------------//
        // �T�[�o�[���烍�O�A�E�g //
        case WindowMenu::ID_LogoutServer:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->LogoutServer();
            break;
        //------------------//
        // ���b�Z�[�W�𑗂� //
        case WindowMenu::ID_SendMessage:
            yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData();
            break;
        //----------//
        // ��L�ȊO //
        default:
            break;
    }
}
