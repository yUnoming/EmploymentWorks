// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SystemNetWorkManager.h"
#include "SystemSceneManager.h"

#include "WindowMenu.h"
#include "SceneManager.h"

#include "TemplateCube.h"
#include "TemplateText.h"

void Ctlan::PrivateSystem::ApplicationSystem::WindowMenu::Create()
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

    // �E�B���h�E�Ƀ��j���[��ǉ�
    SetMenu(Application::GetWindow(), hMenu);
}

void Ctlan::PrivateSystem::ApplicationSystem::WindowMenu::Run(WORD menuID)
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
            SystemManager::SystemSceneManager::CreateNewScene(sceneName);
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
            SceneManager::LoadScene(sceneName);
            break;
        }
        // ===== �쐬�^�u�̏��� ===== //
        //----------//
        // Cube�쐬 //
        case WindowMenu::ID_CreateCube:
        {
            // �V���ɃL���[�u���쐬���A���̃I�u�W�F�N�g�����擾
            GameObject* cubeObject = Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateCube>(1, "Cube");

            // ���b�Z�[�W�f�[�^�쐬
            MessageData messageData;
            messageData.message.header.type = MessageType::CreateCube;
            messageData.message.bodyObject.transform.position = cubeObject->transform->position;
            // ���b�Z�[�W�𑗂鏈�������s
            SystemManager::SystemNetWorkManager::GetServer()->SendMessageData(messageData);
            break;
        }
        //----------//
        // Text�쐬 //
        case WindowMenu::ID_CreateText:
        {
            // �V���Ƀe�L�X�g���쐬
            Ctlan::PublicSystem::SceneManager::GetNowScene()->AddSceneObject<Ctlan::EngineObject::TemplateText>(3, "Text");

            // ���b�Z�[�W�f�[�^�쐬
            MessageData messageData;
            messageData.message.header.type = MessageType::CreateText;
            // ���b�Z�[�W�𑗂鏈�������s
            SystemManager::SystemNetWorkManager::GetServer()->SendMessageData(messageData);
            break;
        }
        // ===== �T�[�o�[�^�u�̏��� ===== //
        //----------------//
        // �T�[�o�[���J�� //
        case WindowMenu::ID_OpenServer:
            SystemManager::SystemNetWorkManager::GetServer()->OpenServer();
            break;
        //------------------//
        // �T�[�o�[����� //
        case WindowMenu::ID_CloseServer:
            SystemManager::SystemNetWorkManager::GetServer()->CloseServer();
            break;
        //--------------------//
        // �T�[�o�[�Ƀ��O�C�� //
        case WindowMenu::ID_LoginServer:
            SystemManager::SystemNetWorkManager::GetServer()->LoginServer();
            break;
        //------------------------//
        // �T�[�o�[���烍�O�A�E�g //
        case WindowMenu::ID_LogoutServer:
            SystemManager::SystemNetWorkManager::GetServer()->LogoutServer();
            break;
        //----------//
        // ��L�ȊO //
        default:
            break;
    }
}
