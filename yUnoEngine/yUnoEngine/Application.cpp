// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "Application.h"
#include "yUno_MainManager.h"
#include "yUno_KeyInputManager.h"
#include "yUno_MouseInputManager.h"

// ������������������������������ //
// �@�@       �}�N���錾          //
// ������������������������������ //
// ----- �E�B���h�E�����T�C�Y -----//
#define WINDOW_HEIGHT 540   // �c��
#define WINDOW_WIDTH  960    // ����

// ----- ���� ----- //
// �E�B���h�E�N���X��
#define WINDOWCLASS_NAME TEXT("yUnoEngine")
// �E�B���h�E��
#define WINDOW_NAME TEXT("yUnoEngine")


// ������������������������������ //
// �@�@       using�錾      �@�@ //
// ������������������������������ //
using namespace yUno_SystemManager;


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
HWND Application::m_hWnd;		// �E�B���h�E�n���h��
UINT Application::m_wndWidth;	// �E�B���h�E�̉���
UINT Application::m_wndHeight;	// �E�B���h�E�̏c��


void Application::Run()
{
    // �A�v���P�[�V�����̏�����������ɍs��ꂽ�H
    if (InitApp())
    {
        MainLoop(); // ���C�����[�v�J�n
    }

    // �I������
    UnInitApp();
}

bool Application::InitApp()
{
    // �E�B���h�E�̏�����������ɍs��ꂽ�H
    if (InitWnd())
    {
        // ����ɍs��ꂽ���Ƃ�`����
        return true;
    }

    // ����ɍs���Ȃ��������Ƃ�`����
    return false;
}

void Application::UnInitApp()
{
    // �E�B���h�E�̏I���������s��
    UnInitWnd();
}

bool Application::InitWnd()
{
    // ===== �E�B���h�E�̐ݒ�E�쐬 ===== //
    // �C���X�^���X�n���h�����擾
    auto hInst = GetModuleHandle(nullptr);

    // �E�B���h�E�̕���ݒ�
    m_wndWidth = WINDOW_WIDTH;     // ����
    m_wndHeight = WINDOW_HEIGHT;   // �c��

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
        return false;   // ����ɍs���Ȃ��������Ƃ�`����

    // �C���X�^���X�n���h������
    m_hInst = hInst;

    // �E�B���h�E�̃T�C�Y��ݒ�
    RECT rc = {};
    rc.right = static_cast<LONG>(m_wndWidth);     // ����
    rc.bottom = static_cast<LONG>(m_wndHeight);   // �c��

    // �E�B���h�E�T�C�Y�𒲐�
    auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    AdjustWindowRect(&rc, style, FALSE);

    // �E�B���h�E���쐬
    m_hWnd = CreateWindowEx(
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
    if (m_hWnd == nullptr)
        return false;   // ����ɍs���Ȃ��������Ƃ�`����

    // �E�B���h�E��\��.
    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    // �E�B���h�E���X�V.
    UpdateWindow(m_hWnd);

    // �E�B���h�E�Ƀt�H�[�J�X��ݒ�.
    SetFocus(m_hWnd);



    // ���������� ���j���[�̐ݒ�E�쐬 ���������� //
    HMENU hMenu = CreateMenu(); // ���j���[�쐬
    const UINT ID_MENU_1 = 1;
    const UINT ID_MENU_2 = 2;
    const UINT ID_MENU_3 = 3;
    const UINT ID_MENU_4 = 4;
    const UINT ID_MENU_5 = 5;

    MENUITEMINFO mii;
    memset(&mii, 0, sizeof(MENUITEMINFO));
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_ID | MIIM_STRING;
    mii.wID = ID_MENU_1;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[���J��");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hMenu, ID_MENU_1, FALSE, &mii);

    mii.wID = ID_MENU_2;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[�����");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hMenu, ID_MENU_2, FALSE, &mii);

    mii.wID = ID_MENU_3;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[�Ƀ��O�C��");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hMenu, ID_MENU_3, FALSE, &mii);

    mii.wID = ID_MENU_4;
    mii.dwTypeData = (LPWSTR)(L"�T�[�o�[���烍�O�A�E�g");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hMenu, ID_MENU_4, FALSE, &mii);

    mii.wID = ID_MENU_5;
    mii.dwTypeData = (LPWSTR)(L"���b�Z�[�W�𑗂�");
    // �쐬�������j���[���A�C�e���Ƃ��Ēǉ�
    InsertMenuItem(hMenu, ID_MENU_5, FALSE, &mii);

    // �E�B���h�E�Ƀ��j���[��ǉ�
    SetMenu(m_hWnd, hMenu);



    // ����ɍs�������Ƃ�`����
    return true;
}

void Application::UnInitWnd()
{
    // �E�B���h�E�̓o�^������.
    if (m_hInst != nullptr)
        UnregisterClass(WINDOWCLASS_NAME, m_hInst);

    m_hInst = nullptr;
    m_hWnd = nullptr;
}

void Application::MainLoop()
{
    // ===== ���������� ===== //
    yUno_MainManager::Init(this);

    MSG msg = {};

    // �E�B���h�E��������܂Ń��[�v
    while (WM_QUIT != msg.message)
    {
        // ���b�Z�[�W���X�V���ꂽ�H
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) == TRUE)
        {
            DispatchMessage(&msg);  // ���b�Z�[�W�̍X�V
            //TranslateMessage(&msg); // �������͂��擾����ꍇ�͂��̊֐����K�v
        }
        else
        {
            // ===== �X�V���� ====== //
            yUno_MainManager::Update();

            // ===== �`�揈�� ===== //
            yUno_MainManager::Draw();
        }
    }

    // ===== �I������ ===== //
    yUno_MainManager::UnInit();
}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // �E�B���h�E�����A�N�V���������������ꍇ
        case WM_CLOSE:
            // �I���m�F�ŁuOK�v�������ꂽ�H
            if (MessageBoxW(NULL, L"�I�����܂����H", L"�I���m�F", MB_OKCANCEL) == IDOK)
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
            yUno_KeyInputManager::SetKeyDown(KeyID);
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
            yUno_KeyInputManager::SetKeyUp(KeyID);
            break;
        }
        // ���j���[�o�[���N���b�N���ꂽ�ꍇ
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            // �T�[�o�[���J��
            case 1:
                yUno_SystemManager::yUno_NetWorkManager::GetServer()->OpenServer();
                break;
            // �T�[�o�[�����
            case 2:
                yUno_SystemManager::yUno_NetWorkManager::GetServer()->CloseServer();
                break;
            // �T�[�o�[�Ƀ��O�C��
            case 3:
                yUno_SystemManager::yUno_NetWorkManager::GetServer()->LoginServer();
                yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData("ServerLogin");
                break;
            // �T�[�o�[���烍�O�A�E�g
            case 4:
                yUno_SystemManager::yUno_NetWorkManager::GetServer()->LogoutServer();
                break;
            // ���b�Z�[�W�𑗂�
            case 5:
                yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData();
                break;
            default:
                break;
            }
            break;
        }

        // �}�E�X�̍��{�^���������ꂽ�ꍇ
        case WM_LBUTTONDOWN:
            // ���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            yUno_MouseInputManager::SetMouseDown(LeftButton);
            break;

        // �}�E�X�̍��{�^���������ꂽ�ꍇ
        case WM_LBUTTONUP:
            // ���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            yUno_MouseInputManager::SetMouseUp(LeftButton);
            break;

        // �}�E�X�̃X�N���[���z�C�[���{�^���������ꂽ�ꍇ
        case WM_MBUTTONDOWN:
            // �X�N���[���z�C�[���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            yUno_MouseInputManager::SetMouseDown(ScrollWheelButton);
            break;

        // �}�E�X�̃X�N���[���z�C�[���{�^���������ꂽ�ꍇ
        case WM_MBUTTONUP:
            // �X�N���[���z�C�[���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            yUno_MouseInputManager::SetMouseUp(ScrollWheelButton);
            break;

        // �}�E�X�X�N���[���z�C�[���{�^������]�����ꍇ
        case WM_MOUSEWHEEL:
            yUno_MouseInputManager::SetMouseWheelState(HIWORD(wParam) % 120 / 16);
            break;

        // �}�E�X�̉E�{�^���������ꂽ�ꍇ
        case WM_RBUTTONDOWN:
            // �E�{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            yUno_MouseInputManager::SetMouseDown(RightButton);
            break;

        // �}�E�X�̉E�{�^���������ꂽ�ꍇ
        case WM_RBUTTONUP:
            // �E�{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            yUno_MouseInputManager::SetMouseUp(RightButton);
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
