// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "yUno_GameObjectManager.h"

#include "Message.h"
#include "yUno_SceneManager.h"
#include "SampleScene.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "SpectatorCamera.h"
#include "Test.h"
#include "Test2.h"

#include "EditScene.h"

#include <SimpleMath.h>

// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
SceneBase* yUno_SceneManager::m_loadedScene;
SceneBase* yUno_SceneManager::m_editScene;
std::unordered_map<std::string, SceneBase*> yUno_SceneManager::m_scenePool;
yUnoEngine::Information::LaunchSceneInformation yUno_SceneManager::m_launchSceneInfo;

void yUno_SceneManager::SaveSceneData()
{
	// �V�[�������擾
	char* sceneName = m_loadedScene->GetSceneName();

	// �V�[���t�@�C�������擾
	char sceneFileName[30] = { "Assets\\" };
	strcat_s(sceneFileName, sizeof(sceneFileName), sceneName);
	strcat_s(sceneFileName, sizeof(sceneFileName), ".dat");

	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, sceneFileName, "wb");
	
	// �J�����Ƃ��o�����H
	if (file)
	{
		// ===== �Z�[�u���� ===== //
		int layerNo = 0;					// ���C���[�ԍ�
		char* objectType = 0;				// �I�u�W�F�N�g�^�C�v
		char* componentType = 0;			// �R���|�[�l���g�^�C�v
		// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
		for (auto objectList : m_loadedScene->GetAllSceneObjects())
		{
			// ���X�g���̃I�u�W�F�N�g�擾
			for (auto object : objectList)
			{
				// ----- �I�u�W�F�N�g�^�C�v�擾���� ----- //
				char tmpObjectType[50];
				char* token;
				char* context;
				objectType = const_cast<char*>(typeid(*object).name());
				ZeroMemory(tmpObjectType, sizeof(tmpObjectType));
				memcpy(tmpObjectType, objectType, strlen(objectType));
				token = strtok_s(tmpObjectType, " ", &context);
				objectType = strtok_s(NULL, " ", &context);

				// ----- �I�u�W�F�N�g�����擾 ----- //
				const char* name = object->GetName();
				yUno_SystemManager::yUno_GameObjectManager::ObjectNameData
					objNameData = yUno_SystemManager::yUno_GameObjectManager::GetObjectNameData(name);

				// �������ݏ���
				char writeData[100] = {};
				sprintf_s(writeData, "%d %s %s %d", layerNo, objectType, objNameData.baseName, objNameData.number);
				fprintf(file, writeData);
				fprintf(file, "\r\n");

				// ���ݎ擾���Ă���I�u�W�F�N�g�̃R���|�[�l���g��S�擾
				std::list<Component*> componentList = object->GetComponentAll();

				int componentNum = componentList.size();
				char componentNumData[2] = {};
				sprintf_s(componentNumData, "%d", componentNum);
				fprintf(file, componentNumData);
				fprintf(file, "\r\n");

				// ���X�g���̃R���|�[�l���g�擾
				for (auto* component : componentList)
				{
					// ----- �R���|�[�l���g�^�C�v�擾���� ----- //
					char tmpComponentType[50];
					componentType = const_cast<char*>(typeid(*component).name());
					ZeroMemory(tmpComponentType, sizeof(tmpComponentType));
					memcpy(tmpComponentType, componentType, strlen(componentType));
					token = strtok_s(tmpComponentType, " ", &context);
					componentType = strtok_s(NULL, " ", &context);
					
					// �������ݏ���
					fprintf(file, componentType);
					fprintf(file, "\r\n");

					// Transform�R���|�[�l���g�H
					if (strcmp(componentType, "PublicSystem::Transform") == 0)
					{
						// �~�����^�ɒ���
						Transform castComponent = *dynamic_cast<Transform*>(component);

						// Position�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.position.x, castComponent.position.y, castComponent.position.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// Rotation�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.rotation.x, castComponent.rotation.y, castComponent.rotation.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// Scale�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.scale.x, castComponent.scale.y, castComponent.scale.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");
					}
				}
			}
			layerNo++;	// ���C���[�ԍ���i�߂�
		}

		// �t�@�C�������
		fclose(file);
	}
}

void yUno_SceneManager::LoadSceneData(const char* loadSceneName)
{
	// �x�[�X�V�[���̐���
	SceneBase* loadScene = new SceneBase(loadSceneName);

	// �V�[���t�@�C�������擾
	char sceneFileName[30] = { "Assets/" };
	strcat_s(sceneFileName, sizeof(sceneFileName), loadSceneName);
	strcat_s(sceneFileName, sizeof(sceneFileName), ".dat");

	// �V�[���t�@�C�����J��
	FILE* file;
	fopen_s(&file, sceneFileName, "r");

	// �J�����Ƃ��ł����H
	if (file)
	{
		// ===== ���[�h���� ===== //
		int layerNo = 0;
		char objectType[100] = { 0 };
		char baseName[100] = { 0 };
		int number = 0;

		// �ǂݍ��ރI�u�W�F�N�g�������Ȃ�܂Ń��[�v
		while (fscanf_s(file, "%d %s %s %d", &layerNo, objectType, (unsigned int)sizeof(objectType),
			&baseName, (unsigned int)sizeof(baseName), &number) != EOF)
		{
			// �ǉ������I�u�W�F�N�g
			GameObject* addedObject = 0;

			// ----- �I�u�W�F�N�g������ݒ� ----- //
			yUno_SystemManager::yUno_GameObjectManager::ObjectNameData objNameData;
			strcpy_s(objNameData.baseName, baseName);					// �ԍ���t�^����O�̖��O
			objNameData.number = number;								// �I�u�W�F�N�g�ԍ�
			// �I�u�W�F�N�g�ԍ����O�ԁH
			if (number == 0) {
				strcpy_s(objNameData.myName, baseName);					// ���̖��̂̂܂�
			}
			else {
				sprintf_s(objNameData.myName, "%s%d", baseName, number);// ���̖��̂ɔԍ���t�^����
			}
			yUno_SystemManager::yUno_GameObjectManager::SetObjectNameData(objNameData);

			// ----- �I�u�W�F�N�g�̒ǉ����� ----- //
			// SpectatorCamera�I�u�W�F�N�g�H
			if (strcmp(objectType, "SpectatorCamera") == 0)
			{
				// �I�u�W�F�N�g�ǉ�
				addedObject = loadScene->LoadSceneObject<SpectatorCamera>(layerNo, objNameData.myName);
			}
			// Test�I�u�W�F�N�g�H
			else if (strcmp(objectType, "Test") == 0)
			{
				addedObject = loadScene->LoadSceneObject<Test>(layerNo, objNameData.myName);
			}
			// Test2�I�u�W�F�N�g�H
			else if (strcmp(objectType, "Test2") == 0)
			{
				addedObject = loadScene->LoadSceneObject<Test2>(layerNo, objNameData.myName);
			}
			// ����ȊO
			else
			{
				addedObject = loadScene->LoadSceneObject<GameObject>(layerNo, objNameData.myName);
			}

			if (addedObject != nullptr)
			{
				// ----- �R���|�[�l���g�̒ǉ����� ----- //
				// �R���|�[�l���g���ǂݎ��
				int componentNum = 0;
				fscanf_s(file, "%d", &componentNum);

				// �R���|�[�l���g���������[�v
				for (int i = 0; i < componentNum; i++)
				{
					// �R���|�[�l���g�^�C�v�擾
					char componentType[100] = { 0 };
					fscanf_s(file, "%s", &componentType, (unsigned int)sizeof(componentType));

					// Transform�R���|�[�l���g�H
					if (strcmp(componentType, "PublicSystem::Transform") == 0)
					{
						float x;
						float y;
						float z;
						fscanf_s(file, "%f, %f, %f", &x, &y, &z);
						addedObject->transform->position = Vector3(x, y, z);
						fscanf_s(file, "%f, %f, %f", &x, &y, &z);
						addedObject->transform->rotation = Vector3(x, y, z);
						fscanf_s(file, "%f, %f, %f", &x, &y, &z);
						addedObject->transform->scale = Vector3(x, y, z);
					}
				}
			}
			addedObject = nullptr;
			ZeroMemory(baseName, sizeof(baseName));
		}
		// �t�@�C�������
		fclose(file);
	}

	m_scenePool[loadSceneName] = loadScene;		// ���[�h�����V�[�����i�[
	m_loadedScene = loadScene;					// ���[�h�����V�[������
}

void yUno_SceneManager::LoadScene()
{
	// �N������V�[���������[�h
	m_launchSceneInfo.Load();

	// �N������V�[�������݂��Ȃ��H
	if (!m_launchSceneInfo.GetLaunchSceneName())
		// �����V�[���쐬
		CreateNewScene("SampleScene");
	// �N������V�[�������݂���
	else
		// �N�����ɊJ���V�[�������[�h
		LoadSceneData(m_launchSceneInfo.GetLaunchSceneName());
	
	// ���[�h�����V�[���̏�����
	m_loadedScene->Init();
}

yUno_SceneManager::yUno_SceneManager()
{
	m_loadedScene = nullptr;
}

void yUno_SceneManager::InitScene()
{
#if _DEBUG
	// �G�f�B�b�g�V�[���̃��[�h
	m_editScene = new yUnoEngine::EditScene();
	m_editScene->Init();
#endif	
	// �����V�[���̃��[�h
	LoadScene();
}

void yUno_SceneManager::UnInitScene()
{
#if _DEBUG
	// �G�f�B�b�g�V�[���̏I������
	m_editScene->UnInit();
	// ���݂̃V�[����Ԃ��Z�[�u
	SaveSceneData();
	// �N������V�[�������Z�[�u
	m_launchSceneInfo.Save();

	// �}�l�[�W���[�̏I������
	yUno_SystemManager::yUno_GameObjectManager::UnInit();
#endif
	// ���݃V�[���̏I������
	m_loadedScene->UnInit();
	delete m_loadedScene;
}

void yUno_SceneManager::UpdateScene()
{
#if _DEBUG
	// �G�f�B�b�g�V�[���̍X�V����
	m_editScene->Update();
#endif
	// ���݃V�[���̍X�V����
	m_loadedScene->Update();
}


#include "renderer.h"
void yUno_SceneManager::DrawScene()
{
	// ���݃V�[���̕`�揈��
	m_loadedScene->Draw();
#if _DEBUG
	// �N���A���邱�ƂŃ}�j�s�����[�^�[���I�u�W�F�N�g�ɔ킹�ĕ`�悳���Ă���
	Renderer::ClearDepthStencilView();
	// �G�f�B�b�g�V�[���̕`�揈��
	m_editScene->Draw();
#endif
}

void yUno_SceneManager::CreateNewScene(const char* sceneName)
{
	// �V�K�V�[������
	SceneBase* newScene = new SceneBase(sceneName);
	// �V�[���ɃJ�����ǉ�
	GameObject* camera = newScene->AddSceneObject<GameObject>(0, "MainCamera");
	camera->AddComponent<Camera>();

	m_scenePool[sceneName] = newScene;		// ���[�h�����V�[�����i�[
	m_loadedScene = newScene;				// ���[�h�����V�[������
}
