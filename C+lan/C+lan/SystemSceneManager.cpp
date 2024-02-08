// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "SystemNetWorkManager.h"
#include "SystemGameObjectManager.h"

#include "Message.h"
#include "SystemSceneManager.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Text.h"
#include "SpectatorCamera.h"

#include "Player.h"
#include "SceneLoader.h"
#include "Timer.h"

#include "TemplateCube.h"
#include "TemplateText.h"

#include "MeteorPool.h"
#include "ParticlePool.h"

#include "EditScene.h"

#include <SimpleMath.h>

// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
Ctlan::PrivateSystem::SceneBase* Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_loadedScene;
Ctlan::PrivateSystem::SceneBase* Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_editScene;
std::unordered_map<std::string, Ctlan::PrivateSystem::SceneBase*> Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_scenePool;
Ctlan::PrivateSystem::Information::LaunchSceneInformation Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_launchSceneInfo;
bool Ctlan::PrivateSystem::SystemManager::SystemSceneManager::isSave;
char Ctlan::PrivateSystem::SystemManager::SystemSceneManager::loadSceneName[30];

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::SaveSceneData()
{
	// �V�[�������擾
	char* sceneName = m_loadedScene->GetSceneName();

	// �V�[���t�@�C�������擾
	char sceneFileName[30] = { "Assets/Scenes/" };
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

		// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
		for (auto objectList : m_loadedScene->GetAllSceneObjects())
		{
			// ���X�g���̃I�u�W�F�N�g�擾
			for (GameObject* object : objectList)
			{
				Meteor* meteor = (Meteor*)object;
				if (strcmp(typeid(*meteor).name(), "class Meteor") == 0)
					continue;
				Particle* particle = (Particle*)object;
				if (strcmp(typeid(*particle).name(), "class Particle") == 0)
					continue;

				// ----- �I�u�W�F�N�g�^�C�v�擾���� ----- //
				char baseObjectType[50];
				char objectType[30] = "GameObject";
				strcpy_s(baseObjectType, typeid(*object).name());
				char* context{};
				char* token = strtok_s(baseObjectType, " ::", &context);
				while (token)
				{
					strcpy_s(objectType, token);
					token = strtok_s(NULL, " ::", &context);
				}

				// ----- �I�u�W�F�N�g�����擾 ----- //
				const char* name = object->GetName();
				Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData
					objNameData = Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::GetObjectNameData(name);

				// �������ݏ���
				char writeData[100] = {};
				sprintf_s(writeData, "%d %s %s %d", layerNo, objectType, objNameData.baseName, objNameData.number);
				fprintf(file, writeData);
				fprintf(file, "\r\n");

				// ���ݎ擾���Ă���I�u�W�F�N�g�̃R���|�[�l���g��S�擾
				std::list<Component*> componentList = object->GetComponentAll();

				int componentNum = static_cast<int>(componentList.size());
				char componentNumData[2] = {};
				sprintf_s(componentNumData, "%d", componentNum);
				fprintf(file, componentNumData);
				fprintf(file, "\r\n");

				// ���X�g���̃R���|�[�l���g�擾
				for (auto* component : componentList)
				{
					// ----- �R���|�[�l���g�^�C�v�擾���� ----- //
					char baseComponentType[50] = {};
					char componentType[30] = "Component";
					strcpy_s(baseComponentType, typeid(*component).name());
					char* context{};
					char* token = strtok_s(baseComponentType, " ::", &context);
					while (token)
					{
						strcpy_s(componentType, token);
						token = strtok_s(NULL, " ::", &context);
					}
					
					// �������ݏ���
					fprintf(file, componentType);
					fprintf(file, "\r\n");

					// Transform�R���|�[�l���g�H
					if (strcmp(componentType, "Transform") == 0)
					{
						// �^�ϊ�
						Transform castComponent = *dynamic_cast<Transform*>(component);

						// position�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.position.x, castComponent.position.y, castComponent.position.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// rotation�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.rotation.x, castComponent.rotation.y, castComponent.rotation.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// scale�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.scale.x, castComponent.scale.y, castComponent.scale.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");
					}
					// Text�R���|�[�l���g�H
					else if (strcmp(componentType, "Text") == 0)
					{
						// �^�ϊ�
						Text castComponent = *dynamic_cast<Text*>(component);
						// text�̒l��������
						sprintf_s(writeData, "%s %s", castComponent.text, "textend");
						fprintf(file, writeData);
						fprintf(file, "\r\n");
						// fontSize�̒l��������
						sprintf_s(writeData, "%f, %f", castComponent.fontSize.x, castComponent.fontSize.y);
						fprintf(file, writeData);
						fprintf(file, "\r\n");
						// leftTopPoint�̒l��������
						sprintf_s(writeData, "%f, %f", castComponent.leftTopPoint.x, castComponent.leftTopPoint.y);
						fprintf(file, writeData);
						fprintf(file, "\r\n");
					}
					else if (strcmp(componentType, "SceneLoader") == 0)
					{
						SceneLoader castSceneLoader = *dynamic_cast<SceneLoader*>(component);
						sprintf_s(writeData, "%s", castSceneLoader.loadSceneName);
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

Ctlan::PrivateSystem::SceneBase* Ctlan::PrivateSystem::SystemManager::SystemSceneManager::LoadSceneData(const char* loadSceneName)
{
	// �x�[�X�V�[���̐���
	SceneBase* loadScene = new SceneBase(loadSceneName);
	// ���[�h�����V�[������
	m_loadedScene = loadScene;

	// �V�[���t�@�C�������擾
	char sceneFileName[100] = {"Assets/Scenes/"};
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
			PrivateSystem::GameObject* addedObject = 0;

			// ----- �I�u�W�F�N�g������ݒ� ----- //
			Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData objNameData;
			strcpy_s(objNameData.baseName, baseName);					// �ԍ���t�^����O�̖��O
			objNameData.number = number;								// �I�u�W�F�N�g�ԍ�
			// �I�u�W�F�N�g�ԍ����O�ԁH
			if (number == 0) {
				strcpy_s(objNameData.myName, baseName);					// ���̖��̂̂܂�
			}
			else {
				sprintf_s(objNameData.myName, "%s%d", baseName, number);// ���̖��̂ɔԍ���t�^����
			}
			Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::SetObjectNameData(objNameData);

			// ----- �I�u�W�F�N�g�̒ǉ����� ----- //
			// TemplateCube�I�u�W�F�N�g�H
			if (strcmp(objectType, "TemplateCube") == 0)
			{
				addedObject = loadScene->LoadSceneObject<EngineObject::TemplateCube>(layerNo, objNameData.myName);
			}
			// TemplateText�I�u�W�F�N�g�H
			else if (strcmp(objectType, "TemplateText") == 0)
			{
				addedObject = loadScene->LoadSceneObject<EngineObject::TemplateText>(layerNo, objNameData.myName);
			}
			else if (strcmp(objectType, "MeteorPool") == 0)
			{
				addedObject = loadScene->LoadSceneObject<MeteorPool>(layerNo, objNameData.myName);
			}
			else if (strcmp(objectType, "ParticlePool") == 0)
			{
				addedObject = loadScene->LoadSceneObject<ParticlePool>(layerNo, objNameData.myName);
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
					if (strcmp(componentType, "Transform") == 0)
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
					else if (strcmp(componentType, "Text") == 0)
					{
						char text[101];		// ���ۂ̃e�L�X�g�p�ϐ�
						char readText[101];	// �ǂݎ��p�e�L�X�g�ϐ�
						bool isCatText = false;
						Vector2 fontSize;
						Vector2 leftTopPoint;
						while (true)
						{
							fscanf_s(file, "%s", &readText, 101);

							// �e�L�X�g�I���H
							if (strcmp(readText, "textend") == 0)
							{
								break;	// ���[�v�𔲂���
							}

							// �e�L�X�g��A������H
							if (isCatText)
							{
								strcat_s(text, " ");		// �󔒂̒ǉ�
								strcat_s(text, readText);	// ���ۂ̃e�L�X�g�p�ϐ��ɘA��
							}
							else
							{
								strcpy_s(text, readText);	// ���ۂ̃e�L�X�g�p�ϐ��ɘA��
								isCatText = true;			// ���񂩂�A������悤�ɂ���
							}
						}
						fscanf_s(file, "%f, %f", &fontSize.x, &fontSize.y);
						fscanf_s(file, "%f, %f", &leftTopPoint.x, &leftTopPoint.y);

						if (!addedObject->GetComponent<Ctlan::PublicSystem::Text>())
							addedObject->AddComponent<Ctlan::PublicSystem::Text>();
						
						Text* textCom = addedObject->GetComponent<Ctlan::PublicSystem::Text>();
						textCom->ChangeText(text);
						textCom->fontSize = fontSize;
						textCom->leftTopPoint = leftTopPoint;
					}
					else if (strcmp(componentType, "Camera") == 0)
					{
						if (!addedObject->GetComponent<Ctlan::PublicSystem::Camera>())
							addedObject->AddComponent<Ctlan::PublicSystem::Camera>();
					}
					else if (strcmp(componentType, "Player") == 0)
					{
						if (!addedObject->GetComponent<Player>())
							addedObject->AddComponent<Player>();
					}
					else if (strcmp(componentType, "Timer") == 0)
					{
						if (!addedObject->GetComponent<Timer>())
							addedObject->AddComponent<Timer>();
					}
					else if (strcmp(componentType, "SceneLoader") == 0)
					{
						if (!addedObject->GetComponent<SceneLoader>())
							addedObject->AddComponent<SceneLoader>();

						char loadSceneName[30];
						fscanf_s(file, "%s", &loadSceneName, 30);

						SceneLoader* sceneLoader = addedObject->GetComponent<SceneLoader>();
						strcpy_s(sceneLoader->loadSceneName, loadSceneName);
					}
				}
			}
			addedObject = nullptr;
			ZeroMemory(baseName, sizeof(baseName));
		}
		// �t�@�C�������
		fclose(file);
	}
	else
		return nullptr;

	m_scenePool[loadSceneName] = loadScene;		// ���[�h�����V�[�����i�[
	return loadScene;
}

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::LoadScene()
{
	// �J�n�V�[���̃��[�h�H
	if (!m_loadedScene)
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
	}
	else
	{
		// ���ɃV�[�������[�h����Ă���H
		if (m_scenePool.count(loadSceneName) > 0 && (m_editScene && !dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay()))
		{
			m_loadedScene = m_scenePool[std::string(loadSceneName)];	// �V�[����ύX����
			ZeroMemory(loadSceneName, sizeof(loadSceneName));
			return;
		}
		// �V�[�������[�h����Ă��Ȃ�
		else
		{
			// ���݃V�[���̏I������
			m_loadedScene->Uninit();

			// ���[�h����V�[�������݂��Ȃ��H
			if (LoadSceneData(loadSceneName) == nullptr)
			{
				// �V�X�e���ʒm��\��
				MessageBoxW(NULL, L"�V�[�������݂��܂���ł���", L"�G���[���b�Z�[�W", MB_OK);
			}
		}
		ZeroMemory(loadSceneName, sizeof(loadSceneName));
	}
}

Ctlan::PrivateSystem::SystemManager::SystemSceneManager::SystemSceneManager()
{
	m_loadedScene = nullptr;
}

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::InitScene()
{
// �f�o�b�O��
#if _DEBUG
	// �G�f�B�b�g�V�[���̃��[�h
	m_editScene = new Ctlan::EngineScene::EditScene();
	m_editScene->Init();
#endif	
// �ʏ폈��
	// �����V�[���̃��[�h
	LoadScene();
	m_loadedScene->Init();
}

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::UninitScene()
{
// �f�o�b�O��
#if _DEBUG
	// �G�f�B�b�g�V�[���̏I������
	static_cast<EngineScene::EditScene*>(m_editScene)->Uninit(isSave);

	// �Z�[�u����H
	if (isSave)
	{
		// ���݂̃V�[����Ԃ��Z�[�u
		SaveSceneData();
		// �N������V�[�������Z�[�u
		m_launchSceneInfo.Save();
	}

	// �}�l�[�W���[�̏I������
	SystemManager::SystemGameObjectManager::Uninit();
	delete[] m_editScene;
#endif
// �ʏ펞
	// ���݃V�[���̏I������
	m_loadedScene->Uninit();
	delete[] m_loadedScene;
}

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::UpdateScene()
{
#if _DEBUG
	// ����̃f���v���C��Ԃ�ۑ�
	bool lateIsDemoPlay = dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay();
	// �G�f�B�b�g�V�[���̍X�V����
	m_editScene->Update();

	// �f���v���C���J�n���ꂽ�H
	if (!lateIsDemoPlay && dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay())
	{
		// �V�[���̃Z�[�u
		SaveSceneData();
		// ���[�h����V�[������ۑ�
		strcpy_s(loadSceneName, m_loadedScene->GetSceneName());
		// �V�[���������[�h
		LoadScene();
	}
	// �f���v���C���I�������H
	else if (lateIsDemoPlay && !dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay())
	{
		// �V�[���������[�h
		LoadSceneData(m_launchSceneInfo.GetLaunchSceneName());
		ZeroMemory(loadSceneName, sizeof(loadSceneName));
	}
#endif
	// ���݃V�[���̍X�V����
	m_loadedScene->Update();
	if (strlen(loadSceneName) > 0)
		LoadScene();
}


#include "renderer.h"
void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::DrawScene()
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

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::CreateNewScene(const char* sceneName)
{
	// �V�K�V�[������
	SceneBase* newScene = new SceneBase(sceneName);
	// �V�[���ɃJ�����ǉ�
	GameObject* camera = newScene->AddSceneObject<GameObject>(0, "MainCamera");
	camera->AddComponent<Camera>();

	m_scenePool[sceneName] = newScene;		// ���[�h�����V�[�����i�[
	m_loadedScene = newScene;				// ���[�h�����V�[������
}
