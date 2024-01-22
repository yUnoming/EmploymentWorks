// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SystemNetWorkManager.h"
#include "SystemMainManager.h"
#include "SystemTimeManager.h"
#include "SystemKeyInputManager.h"
#include "SystemMouseInputManager.h"
#include "SystemCollisionManager.h"

#include "renderer.h"
#include "FileReader.h"

#include "EditScene.h"


// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
bool Ctlan::PrivateSystem::SystemManager::SystemMainManager::m_demoPlay;


void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Init(Application* app)
{
    // ===== �V�X�e���̏��������� ===== //
    // ����
    SystemTimeManager::Init();
    // �l�b�g���[�N
    SystemNetWorkManager::Init();
    // �����_���[
    Renderer::Init(app);

    // ----- �W���t�H���g�ݒ� ----- //
    FileReader::ReadTtfFile(L"Assets\\Fonts\\calibri.ttf", "Calibri");

    // ===== ���C���̏��������� ===== //
    // �V�[���𗧂��グ��
    SystemSceneManager::InitScene();
}

void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Uninit()
{
    // ===== ���C���̏��������� ===== //
    // �l�b�g���[�N�I��
    SystemNetWorkManager::Uninit();

    // �V�[���̏I��
    SystemSceneManager::UninitScene();
}

void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Update()
{
    // ===== �V�X�e���̍X�V���� ===== //
    // ����
    SystemTimeManager::Update();

    // �L�[����
    SystemKeyInputManager::Update();

    // ===== ���C���̍X�V���� ===== //
    // ----- �f���v���C�̐؂�ւ�----- //
    // ���jEnter�L�[�������ꂽ�H
    //if (KeyInput::GetKeyDown_Trigger(KeyName::Enter))
    //    m_DemoPlay ^= true;  // �f���v���C�̏�Ԃ�؂�ւ���

    // �V�[���̍X�V
    SystemSceneManager::UpdateScene();
    // �����蔻��̌v�Z
    SystemCollisionManager::CalculationCollision();

    // ���݂̃L�[���͏�Ԃ�ۑ�����
    SystemKeyInputManager::KeepNowKeyInfo();
    // ���݂̃}�E�X���͏�Ԃ�ۑ�����
    SystemMouseInputManager::KeepNowMouseState();
}

void Ctlan::PrivateSystem::SystemManager::SystemMainManager::Draw()
{
    // ===== ���C���̕`�揈�� ===== //
    // �`��̑O����
    Renderer::Begin();

    // �V�[���̕`��
    SystemSceneManager::DrawScene();

    // �`��̌㏈��
    Renderer::End();
}

