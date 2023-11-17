// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "renderer.h"
#include "FileReader.h"

#include "yUno_MainManager.h"
#include "yUno_TimeManager.h"
#include "yUno_KeyInputManager.h"
#include "yUno_MouseInputManager.h"

#include "SampleScene.h"

// ������������������������������ //
// �@�@		 using�錾 	    	  //
// ������������������������������ //
using namespace yUno_SystemManager;
using namespace PublicSystem;


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
bool yUno_MainManager::m_DemoPlay;
yUno_SceneManager*  yUno_MainManager::m_NowScene;


void yUno_MainManager::Init(Application* app)
{
    // ===== �V�X�e���̏��������� ===== //
    // ����
    yUno_TimeManager::Init();
    // �l�b�g���[�N
    yUno_NetWorkManager::Init();
    // �����_���[
    Renderer::Init(app);

    // ----- shader�ݒ� ----- //
    // �e�ϐ�
    ID3D11VertexShader* VertexShader{};
    ID3D11PixelShader* PixelShader{};
    ID3D11InputLayout* VertexLayout{};

    // ���_�V�F�[�_�[�A�s�N�Z���V�F�[�_�쐬
    Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "Assets\\Shaders\\unlitTextureVS.cso");
    Renderer::CreatePixelShader(&PixelShader, "Assets\\Shaders\\unlitTexturePS.cso");

    // ���̓��C�A�E�g�ݒ�
    Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

    // �V�F�[�_�ݒ�
    Renderer::GetDeviceContext()->VSSetShader(VertexShader, nullptr, 0);
    Renderer::GetDeviceContext()->PSSetShader(PixelShader, nullptr, 0);


    // ----- �W���t�H���g�ݒ� ----- //
    FileReader::ReadTtfFile(L"Assets\\Fonts\\calibri.ttf", "Calibri");

    // ===== ���C���̏��������� ===== //
    // �V�[���𗧂��グ��
    m_NowScene = new yUno_SceneManager();
    m_NowScene->LoadScene<SampleScene>();
}

void yUno_MainManager::UnInit()
{
    // ===== ���C���̏��������� ===== //
    // �V�[���̏I��
    m_NowScene->UnInitBase();
    // �V�[���̍폜
    delete m_NowScene;
    
    // �l�b�g���[�N�I��
    yUno_NetWorkManager::UnInit();
}

void yUno_MainManager::Update()
{
    // ===== �V�X�e���̍X�V���� ===== //
    // ����
    yUno_TimeManager::Update();

    // �L�[����
    yUno_KeyInputManager::Update();

    // ===== ���C���̍X�V���� ===== //
    // ----- �f���v���C�̐؂�ւ�----- //
    // ���jEnter�L�[�������ꂽ�H
    //if (KeyInput::GetKeyDown_Trigger(KeyName::Enter))
    //    m_DemoPlay ^= true;  // �f���v���C�̏�Ԃ�؂�ւ���

    // �V�[���̍X�V
    m_NowScene->UpdateBase();

    // ���݂̃L�[���͏�Ԃ�ۑ�����
    yUno_KeyInputManager::KeepNowKeyInfo();
    // ���݂̃}�E�X���͏�Ԃ�ۑ�����
    yUno_MouseInputManager::KeepNowMouseState();
}

void yUno_MainManager::Draw()
{
    // ===== ���C���̕`�揈�� ===== //
    // �`��̑O����
    Renderer::Begin();

    // �V�[���̕`��
    m_NowScene->DrawBase();

    // �`��̌㏈��
    Renderer::End();
}

