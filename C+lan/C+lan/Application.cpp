// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Application.h"
#include "WindowMenu.h"
#include "SystemMainManager.h"
#include "SystemKeyInputManager.h"
#include "SystemMouseInputManager.h"

// ������������������������������ //
// �@�@       �}�N���錾          //
// ������������������������������ //
// ----- �E�B���h�E�����T�C�Y -----//
#define WINDOW_HEIGHT 540   // �c��
#define WINDOW_WIDTH  960    // ����

// ----- ���� ----- //
// �E�B���h�E�N���X��
#define WINDOWCLASS_NAME TEXT("C+lan")
// �E�B���h�E��
#define WINDOW_NAME TEXT("C+lan")


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
HWND Ctlan::PrivateSystem::Application::m_hWnd;		// �E�B���h�E�n���h��
UINT Ctlan::PrivateSystem::Application::m_wndWidth;	// �E�B���h�E�̉���
UINT Ctlan::PrivateSystem::Application::m_wndHeight;	// �E�B���h�E�̏c��


void Ctlan::PrivateSystem::Application::Run()
{
    // �A�v���P�[�V�����̏�����������ɍs��ꂽ�H
    if (InitApp())
    {
        MainLoop(); // ���C�����[�v�J�n
    }

    // �I������
    UninitApp();
}

bool Ctlan::PrivateSystem::Application::InitApp()
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

void Ctlan::PrivateSystem::Application::UninitApp()
{
    // �E�B���h�E�̏I���������s��
    UninitWnd();
}

bool Ctlan::PrivateSystem::Application::InitWnd()
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

#if _DEBUG
    // ----- �E�B���h�E�̃��j���[�쐬 ----- //
    Ctlan::PrivateSystem::ApplicationSystem::WindowMenu::Create();
#endif

    // ����ɍs�������Ƃ�`����
    return true;
}

void Ctlan::PrivateSystem::Application::UninitWnd()
{
    // �E�B���h�E�̓o�^������.
    if (m_hInst != nullptr)
        UnregisterClass(WINDOWCLASS_NAME, m_hInst);

    m_hInst = nullptr;
    m_hWnd = nullptr;
}

void Ctlan::PrivateSystem::Application::MainLoop()
{
    // ===== ���������� ===== //
    Ctlan::PrivateSystem::SystemManager::SystemMainManager::Init(this);

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
            Ctlan::PrivateSystem::SystemManager::SystemMainManager::Update();

            // ===== �`�揈�� ===== //
            Ctlan::PrivateSystem::SystemManager::SystemMainManager::Draw();
        }
    }

    // ===== �I������ ===== //
    Ctlan::PrivateSystem::SystemManager::SystemMainManager::Uninit();
}

LRESULT CALLBACK Ctlan::PrivateSystem::Application::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // �E�B���h�E�����A�N�V���������������ꍇ
        case WM_CLOSE:
            // �I���m�F�ŁuOK�v�������ꂽ�H
            if (MessageBox(NULL, L"�I�����܂����H", L"�I���m�F", MB_OKCANCEL) == IDOK)
            {
                // �Z�[�u�m�F�ŁuOK�v�������ꂽ�H
                if (MessageBox(NULL, L"���݂̕ύX���Z�[�u���܂����H", L"�Z�[�u�m�F", MB_OKCANCEL) == IDOK)
                {
                    // �Z�[�u���邱�Ƃ�`����
                    Ctlan::PrivateSystem::SystemManager::SystemSceneManager::SaveScene();
                }
                // �E�B���h�E�����
                DestroyWindow(hWnd);
            }
            // �I���m�F�ŁuCANCEL�v�������ꂽ
            else
            {
                // �E�B���h�E����Ȃ����߂ɁAWM_NULL����
                msg = WM_NULL;
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
            WORD KeyID = LOWORD(wParam);

            // �����ꂽ�L�[��ۑ�����֐������s
            Ctlan::PrivateSystem::SystemManager::SystemKeyInputManager::SetKeyDown(KeyID);
            break;
        }

        // �L�[�������ꂽ�ꍇ
        case WM_KEYUP:
        {
            // ������Ă���L�[���擾
            WORD KeyID = LOWORD(wParam);

            // �����ꂽ�L�[��ۑ�����֐������s
            Ctlan::PrivateSystem:: SystemManager::SystemKeyInputManager::SetKeyUp(KeyID);
            break;
        }
        // ���j���[�o�[���N���b�N���ꂽ�ꍇ
        case WM_COMMAND:
        {
            // �N���b�N���ꂽ���e�̎��s����
            Ctlan::PrivateSystem::ApplicationSystem::WindowMenu::Run((LOWORD(wParam)));
            break;
        }

        // �}�E�X�̍��{�^���������ꂽ�ꍇ
        case WM_LBUTTONDOWN:
            // ��ʊO�Ŕ���ł���悤�L���v�`���[�J�n
            SetCapture(hWnd);
            // ���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseDown(LeftButton);
            break;

        // �}�E�X�̍��{�^���������ꂽ�ꍇ
        case WM_LBUTTONUP:
            // �L���v�`���[���I��
            ReleaseCapture();
            // ���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseUp(LeftButton);
            break;

        // �}�E�X�̃X�N���[���z�C�[���{�^���������ꂽ�ꍇ
        case WM_MBUTTONDOWN:
            // ��ʊO�Ŕ���ł���悤�L���v�`���[�J�n
            SetCapture(hWnd);
            // �X�N���[���z�C�[���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseDown(ScrollWheelButton);
            break;

        // �}�E�X�̃X�N���[���z�C�[���{�^���������ꂽ�ꍇ
        case WM_MBUTTONUP:
            // �L���v�`���[���I��
            ReleaseCapture();
            // �X�N���[���z�C�[���{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseUp(ScrollWheelButton);
            break;

        // �}�E�X�X�N���[���z�C�[���{�^������]�����ꍇ
        case WM_MOUSEWHEEL:
            Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseWheelState(HIWORD(wParam) % 120 / 16);
            break;

        // �}�E�X�̉E�{�^���������ꂽ�ꍇ
        case WM_RBUTTONDOWN:
            // ��ʊO�Ŕ���ł���悤�L���v�`���[�J�n
            SetCapture(hWnd);
            // �E�{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseDown(RightButton);
            break;

        // �}�E�X�̉E�{�^���������ꂽ�ꍇ
        case WM_RBUTTONUP:
            // �L���v�`���[���I��
            ReleaseCapture();
            // �E�{�^���������ꂽ���Ƃ�ݒ肷��֐������s
            Ctlan::PrivateSystem::SystemManager::SystemMouseInputManager::SetMouseUp(RightButton);
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
