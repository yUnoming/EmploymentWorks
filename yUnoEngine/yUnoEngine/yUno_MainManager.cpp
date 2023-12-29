// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "yUno_MainManager.h"
#include "yUno_TimeManager.h"
#include "yUno_KeyInputManager.h"
#include "yUno_MouseInputManager.h"
#include "yUno_CollisionManager.h"

#include "renderer.h"
#include "FileReader.h"


#include "SampleScene.h"
#include "EditScene.h"

// ������������������������������ //
// �@�@		 using�錾 	    	  //
// ������������������������������ //
using namespace yUno_SystemManager;
using namespace PublicSystem;


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
bool yUno_MainManager::m_demoPlay;


void yUno_MainManager::Init(Application* app)
{
    // ===== �V�X�e���̏��������� ===== //
    // ����
    yUno_TimeManager::Init();
    // �l�b�g���[�N
    yUno_NetWorkManager::Init();
    // �����_���[
    Renderer::Init(app);

    // ----- �W���t�H���g�ݒ� ----- //
    FileReader::ReadTtfFile(L"Assets\\Fonts\\calibri.ttf", "Calibri");

    // ===== ���C���̏��������� ===== //
    // �V�[���𗧂��グ��
    yUno_SceneManager::InitScene();
}

void yUno_MainManager::UnInit()
{
    // ===== ���C���̏��������� ===== //
    // �l�b�g���[�N�I��
    yUno_NetWorkManager::UnInit();

    // �V�[���̏I��
    yUno_SceneManager::UnInitScene();
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
    yUno_SceneManager::UpdateScene();
    // �����蔻��̌v�Z
    yUno_CollisionManager::CalculationCollision();

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
    yUno_SceneManager::DrawScene();

    // �`��̌㏈��
    Renderer::End();
}

