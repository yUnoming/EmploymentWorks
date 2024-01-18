#include "EditScene.h"
#include "SceneManager.h"
#include "Text.h"
#include "KeyInput.h"

void yUnoEngine::EditScene::Init()
{
	// ===== �ҏW�p�J�����̐��� ===== //
	m_spectatorCamera = AddSceneObject<SpectatorCamera>(0, "SpectatorCamera");

	// ===== ���[�h���� ===== //
	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, "Assets\\SceneEditor.dat", "rb");

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
		m_sceneEditorData.cameraComponent = *m_spectatorCamera->GetComponent<Camera>();
	}


	// ===== �}�j�s�����[�^�[�p�I�u�W�F�N�g�̐��� ===== //
	// ----- �ړ� ----- //
	m_manipulator_MoveX = AddSceneObject<Manipulator::Manipulator_MoveX>(1, "Manipulator_MoveX");
	m_manipulator_MoveY = AddSceneObject<Manipulator::Manipulator_MoveY>(1, "Manipulator_MoveY");
	m_manipulator_MoveZ = AddSceneObject<Manipulator::Manipulator_MoveZ>(1, "Manipulator_MoveZ");
}

void yUnoEngine::EditScene::UnInit()
{
	// ===== �Z�[�u���� ===== //
	// �V�[���ҏW�Ɏg���f�[�^���쐬
	m_sceneEditorData.transformComponent = *m_spectatorCamera->transform;
	m_sceneEditorData.cameraComponent = *m_spectatorCamera->GetComponent<Camera>();

	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, "Assets\\SceneEditor.dat", "wb");

	// �J�����Ƃ��o�����H
	if (file)
	{
		fwrite(&m_sceneEditorData, sizeof(SceneEditorData), 1, file);
		fclose(file);
	}

	// �V�[���̊�{�I�ȏI�����������s
	SceneBase::UnInit();
}

void yUnoEngine::EditScene::Update()
{
	// �I�u�W�F�N�g���N���b�N�����H
	if (m_spectatorCamera->GetClickedObject() != nullptr)
	{
		// �e�L�X�g�ł͂Ȃ��H
		if (!m_spectatorCamera->GetClickedObject()->GetComponent<Text>())
		{
			// ===== �}�j�s�����[�^�[�̕\������ ===== //
			// ----- �ړ� ----- //
			// X������
			m_manipulator_MoveX->isActive = true;
			m_manipulator_MoveX->transform->parent = m_spectatorCamera->GetClickedObject();
			// Y������
			m_manipulator_MoveY->isActive = true;
			m_manipulator_MoveY->transform->parent = m_spectatorCamera->GetClickedObject();
			// Z������
			m_manipulator_MoveZ->isActive = true;
			m_manipulator_MoveZ->transform->parent = m_spectatorCamera->GetClickedObject();
		}
	}
	else
	{
		// ===== �}�j�s�����[�^�[�̔�\������ ===== //
		// ----- �ړ� ----- //
		// X������
		m_manipulator_MoveX->isActive = false;
		m_manipulator_MoveX->transform->parent = nullptr;
		// Y������
		m_manipulator_MoveY->isActive = false;
		m_manipulator_MoveY->transform->parent = nullptr;
		// Z������
		m_manipulator_MoveZ->isActive = false;
		m_manipulator_MoveZ->transform->parent = nullptr;
	}

	// F1�L�[�������ꂽ�H
	if (KeyInput::GetKeyDownTrigger(KeyName::F1))
	{
		isDemoPlay = isDemoPlay ? false : true;	// �f���v���C��Ԃ�؂�ւ���
	}

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			// �A�N�e�B�u��ԁH
			if (object->isActive)
				object->UpdateBase();	// �X�V����
		}
	}
}

void yUnoEngine::EditScene::Draw()
{
	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_sceneObjectList)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			// �A�N�e�B�u��ԁH
			if (object->isActive)
				object->DrawBase();	// �`�揈��
		}
	}
}
