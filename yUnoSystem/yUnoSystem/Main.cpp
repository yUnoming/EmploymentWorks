// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <Windows.h>
#include <iostream>  // cin, cout���g�p���邽��
#include <tchar.h>   // _T���g�p���邽��

#include "yUno_KeyInputManager.h"
#include "yUno_TimeManager.h"

#include "KeyInput.h"
#include "Time.h"

// ������������������������������ //
// �@�@      using�錾 �@         //
// ������������������������������ //
using namespace yUno_SystemManager;
using namespace System;

// ������������������������������ //
// �@�@   �v���g�^�C�v�錾        //
// ������������������������������ //
// �E�B���h�E�Y�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

// ������������������������������ //
// �@�@       �}�N���錾          //
// ������������������������������ //
// �E�B���h�E�T�C�Y
#define WINDOW_HEIGHT 540   // �c��
#define WINDOW_WIDTH 960    // ����

// ����
#define WINDOWCLASS_NAME _T("�E�B���h�E�N���X��")   // �E�B���h�E�N���X���i�N�����A��ʉ��̃A�C�R���ɃJ�[�\�������킹�����j
#define WINDOW_NAME _T("�E�B���h�E��")              // �E�B���h�E���i�N�����A�X�N���[����j

int main()
{
    // ���������� �E�B���h�E�̐ݒ�E�쐬 ���������� //
    // �C���X�^���X�n���h�����擾
    auto hInst = GetModuleHandle(nullptr);

    // �E�B���h�E�̐ݒ�
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);                         // �T�C�Y�i�o�C�g�P�ʁj
    wc.style = CS_HREDRAW | CS_VREDRAW;                     // �X�^�C��
    wc.lpfnWndProc = WndProc;                               // �E�B���h�E�v���V�[�W���ւ̃|�C���^�[
    wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);            // �N���X�A�C�R���ւ̃n���h��
    wc.hCursor = LoadCursor(hInst, IDC_HELP);               // �N���X�J�[�\���ւ̃n���h��
    wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);  // �N���X�̔w�i�u���V�ւ̃n���h��
    wc.lpszMenuName = nullptr;                              // �N���X���j���[�̃��\�[�X�����w�肷��null�ŏI��镶����ւ̃|�C���^�[
    wc.lpszClassName = WINDOWCLASS_NAME;                   // �E�B���h�E�N���X��
    wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);          // �E�B���h�E�N���X�Ɋ֘A�t�����Ă��鏬���ȃA�C�R���ւ̃n���h��

    // �E�B���h�E�̓o�^
    if (!RegisterClassEx(&wc))
    {
        // �E�B���h�E�N���X�̓o�^���������s���Ȃ������ꍇ
        return false;
    }

    // �E�B���h�E�̃T�C�Y��ݒ�
    RECT rc = {};
    rc.right = static_cast<LONG>(WINDOW_WIDTH);     // ����
    rc.bottom = static_cast<LONG>(WINDOW_HEIGHT);   // �c��

    // �E�B���h�E�T�C�Y�𒲐�
    auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    AdjustWindowRect(&rc, style, FALSE);

    // �E�B���h�E���쐬
    HWND hWnd = CreateWindowEx(
        0,                          // �g���E�B���h�E�X�^�C��
        WINDOWCLASS_NAME,           // �E�B���h�E�N���X��
        WINDOW_NAME,                // �E�B���h�E��
        style,                      // �E�B���h�E�X�^�C��
        CW_USEDEFAULT,              // �E�B���h�E���̍��W�l
        CW_USEDEFAULT,              // �E�B���h�E��̍��W�l
        rc.right - rc.left,         // �E�B���h�E�̕�         
        rc.bottom - rc.top,         // �E�B���h�E�̍���
        nullptr,                    // �쐬�����E�B���h�E�̐e�E�B���h�E or ���L�҃E�B���h�E�ւ̃n���h��
        nullptr,                    // ���j���[�ւ̃n���h��
        hInst,                      // �C���X�^���X�ւ̃n���h��
        nullptr);                   // �E�B���h�E�ɓn�����l�ւ̃|�C���^�[

    // �E�B���h�E���쐬�o���Ȃ������H
    if (hWnd == nullptr)
    {
        return false;
    }

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

    // �E�B���h�E��\��.
    ShowWindow(hWnd, SW_SHOWNORMAL);

    // �E�B���h�E���X�V.
    UpdateWindow(hWnd);

    // �E�B���h�E�Ƀt�H�[�J�X��ݒ�.
    SetFocus(hWnd);

    // ���������� �V�X�e���̏��������� ���������� //
    // ����
    yUno_TimeManager::Init();

    // ���������� ���C�����[�v ���������� //
    MSG msg = {};

    // �E�B���h�E��������܂Ń��[�v
    while (WM_QUIT != msg.message)
    {
        // ���b�Z�[�W���X�V���ꂽ�H
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) == true)
        {
            DispatchMessage(&msg);  // ���b�Z�[�W�̍X�V
            //TranslateMessage(&msg); // �������͂��擾����ꍇ�͂��̊֐����K�v
        }
        else
        {
            // ���������� �V�X�e���̍X�V���� ���������� //
            // ����
            yUno_TimeManager::Update();
           
            // �L�[����
            yUno_KeyInputManager::Update();
            
            // ���������� �Q�[�������� ���������� //
            // KeyInput�̃e�X�g�FLShift�������ꂽ�H
            if (KeyInput::GetKeyDown_Trigger(KeyName::LeftShift))
            {
                std::cout << "Pushed LShift" << std::endl;
            }

            // KeyInput�̃e�X�g�FRShift�������ꂽ�H
            if (KeyInput::GetKeyDown_Trigger(KeyName::RightShift))
            {
                std::cout << "Pushed RShift" << std::endl;
            }

            // ���݂̃L�[���͏�Ԃ�ۑ�����
            yUno_KeyInputManager::Keep_Now_KeyInfo();
        }
    }

    return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    // �E�B���h�E�����A�N�V���������������ꍇ
    case WM_CLOSE:
        // �I���m�F�ŁuOK�v�������ꂽ�H
        if (MessageBox(NULL, _T("�I�����܂����H"), _T("�I���m�F"), MB_OKCANCEL) == IDOK)
        {
            // �E�B���h�E�����
            DestroyWindow(hWnd);
        }
        break;

    // �E�B���h�E�������ꍇ
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    // �L�[�������ꂽ�ꍇ
    case WM_KEYDOWN:
    {
        // ������Ă���L�[���擾
        WORD KeyID = HIWORD(lParam);

        // ���߂��l���傫������
        if (KeyID > 10000)
            KeyID -= 49152;  // �~�����l�ɏC������
        // ���߂��l���܂��傫������
        if (KeyID > 10000)
            KeyID -= 32768;  // �~�����l�ɂ���ɏC������

        // �����ꂽ�L�[��ۑ�����֐������s
        yUno_KeyInputManager::Set_KeyDown(KeyID);
        break;
    }

    // �L�[�������ꂽ�ꍇ
    case WM_KEYUP:
    {
        // ������Ă���L�[���擾
        WORD KeyID = HIWORD(lParam);

        // ���߂��l���傫������
        if (KeyID > 10000)
            KeyID -= 49152;  // �~�����l�ɏC������
        // ���߂��l���܂��傫������
        if (KeyID > 10000)
            KeyID -= 32768;  // �~�����l�ɂ���ɏC������

        // �����ꂽ�L�[��ۑ�����֐������s
        yUno_KeyInputManager::Set_KeyUp(KeyID);
        break;
    }

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}
