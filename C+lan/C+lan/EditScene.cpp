#include "EditScene.h"
#include "SceneManager.h"
#include "Text.h"
#include "KeyInput.h"
#include "TemplateCube.h"
#include "Player.h"

void Ctlan::EngineScene::EditScene::Init()
{
	// ===== �ҏW�p�J�����̐��� ===== //
	m_spectatorCamera = AddSceneObject<EngineObject::SpectatorCamera>(0, "SpectatorCamera");

	// ===== ���[�h���� ===== //
	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, "Assets/Scenes/SceneEditor.dat", "rb");

	// �J�����Ƃ��o�����H
	if (file)
	{
		// �f�[�^�����[�h
		fread(&m_sceneEditorData, sizeof(SceneEditorData), 1, file);
		// �g�����X�t�H�[��������
		m_spectatorCamera->transform->position = m_sceneEditorData.transformComponent.position;
		m_spectatorCamera->transform->rotation = m_sceneEditorData.transformComponent.rotation;
		m_spectatorCamera->transform->scale = m_sceneEditorData.transformComponent.scale;
		// �J����������
		Camera* cam = m_spectatorCamera->GetComponent<Camera>();
		cam->nearClip = m_sceneEditorData.cameraComponent.nearClip;
		cam->farClip = m_sceneEditorData.cameraComponent.farClip;
		cam->fieldOfView = m_sceneEditorData.cameraComponent.fieldOfView;
		fclose(file);
	}
	// �J�����Ƃ��o���Ȃ�����
	else
	{
		// �V�[���ҏW�Ɏg���f�[�^���쐬
		m_sceneEditorData.transformComponent = *m_spectatorCamera->transform;
		m_sceneEditorData.cameraComponent = *m_spectatorCamera->GetComponent<Ctlan::PublicSystem::Camera>();
	}


	// ===== �}�j�s�����[�^�[�p�I�u�W�F�N�g�̐��� ===== //
	// ----- �ړ� ----- //
	m_positionXGizmo = AddSceneObject<Ctlan::EngineObject::Gizmo::PositionXGizmo>(1, "PositionXGizmo");
	m_positionYGizmo = AddSceneObject<Ctlan::EngineObject::Gizmo::PositionYGizmo>(1, "PositionYGizmo");
	m_positionZGizmo = AddSceneObject<Ctlan::EngineObject::Gizmo::PositionZGizmo>(1, "PositionZGizmo");
}

void Ctlan::EngineScene::EditScene::Uninit(bool isSave)
{
	// �Z�[�u����H
	if (isSave)
	{
		// ===== �Z�[�u���� ===== //
		// �V�[���ҏW�Ɏg���f�[�^���쐬
		m_sceneEditorData.transformComponent = *m_spectatorCamera->transform;
		m_sceneEditorData.cameraComponent = *m_spectatorCamera->GetComponent<Camera>();

		// �V�[���t�@�C�����J��
		FILE* file;
		fopen_s(&file, "Assets/Scenes/SceneEditor.dat", "wb");

		// �J�����Ƃ��o�����H
		if (file)
		{
			fwrite(&m_sceneEditorData, sizeof(SceneEditorData), 1, file);
			fclose(file);
		}

	}

	// �V�[���̊�{�I�ȏI�����������s
	SceneBase::Uninit();
}

void Ctlan::EngineScene::EditScene::Update()
{
	// �I�u�W�F�N�g���N���b�N�����H
	if (m_spectatorCamera->GetClickedObject() != nullptr)
	{
		// �e�L�X�g�ł͂Ȃ��H
		if (!m_spectatorCamera->GetClickedObject()->GetComponent<Ctlan::PublicSystem::Text>())
		{
			// ===== �}�j�s�����[�^�[�̕\������ ===== //
			// ----- �ړ� ----- //
			// X������
			m_positionXGizmo->isActive = true;
			m_positionXGizmo->transform->parent = m_spectatorCamera->GetClickedObject();
			// Y������
			m_positionYGizmo->isActive = true;
			m_positionYGizmo->transform->parent = m_spectatorCamera->GetClickedObject();
			// Z������
			m_positionZGizmo->isActive = true;
			m_positionZGizmo->transform->parent = m_spectatorCamera->GetClickedObject();
		}
		else
		{
			// ===== �}�j�s�����[�^�[�̔�\������ ===== //
			// ----- �ړ� ----- //
			// X������
			m_positionXGizmo->isActive = false;
			m_positionXGizmo->transform->parent = nullptr;
			// Y������
			m_positionYGizmo->isActive = false;
			m_positionYGizmo->transform->parent = nullptr;
			// Z������
			m_positionZGizmo->isActive = false;
			m_positionZGizmo->transform->parent = nullptr;
		}
	}
	else
	{
		// ===== �}�j�s�����[�^�[�̔�\������ ===== //
		// ----- �ړ� ----- //
		// X������
		m_positionXGizmo->isActive = false;
		m_positionXGizmo->transform->parent = nullptr;
		// Y������
		m_positionYGizmo->isActive = false;
		m_positionYGizmo->transform->parent = nullptr;
		// Z������
		m_positionZGizmo->isActive = false;
		m_positionZGizmo->transform->parent = nullptr;
	}

	// F1�L�[�������ꂽ�H
	if (KeyInput::GetKeyDownTrigger(KeyName::F1))
	{
		isDemoPlay = isDemoPlay ? false : true;	// �f���v���C��Ԃ�؂�ւ���
		
		// �f���v���C�ɐ؂�ւ�����H
		if (isDemoPlay)
		{
			// ===== �}�j�s�����[�^�[�̔�\������ ===== //
			// ----- �ړ� ----- //
			// X������
			m_positionXGizmo->isActive = false;
			m_positionXGizmo->transform->parent = nullptr;
			// Y������
			m_positionYGizmo->isActive = false;
			m_positionYGizmo->transform->parent = nullptr;
			// Z������
			m_positionZGizmo->isActive = false;
			m_positionZGizmo->transform->parent = nullptr;

			// �N���b�N��Ԃ�����
			m_spectatorCamera->ReleaseClickedObject();
		}
	}
	// �f���v���C���Ȃ�I�u�W�F�N�g�̍X�V�͍s��Ȃ�
	if (isDemoPlay)return;

	// ===== �G�f�B�b�g�V�[���I�u�W�F�N�g�̍X�V���� ===== //
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (Ctlan::PrivateSystem::GameObject* object : objectList)
		{
			// �A�N�e�B�u��ԁH
			if (object->isActive)
				object->UpdateBase();	// �X�V����
		}
	}
}

void Ctlan::EngineScene::EditScene::Draw()
{
	// �f���v���C���Ȃ�I�u�W�F�N�g�̕`��͍s��Ȃ�
	if (isDemoPlay)return;

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (Ctlan::PrivateSystem::GameObject* object : objectList)
		{
			// �A�N�e�B�u��ԁH
			if (object->isActive)
				object->DrawBase();	// �`�揈��
		}
	}


}
