// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_NetWorkManager.h"
#include "Message.h"
#include "yUno_SceneManager.h"
#include "SampleScene.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "SpectatorCamera.h"
#include "Test.h"
#include "Test2.h"

#include <SimpleMath.h>

// ������������������������������������ //
// �@�@   static�����o�ϐ��̒�`        //
// ������������������������������������ //
std::array<std::list<GameObject*>, 4> yUno_SceneManager::m_sceneObject;
yUno_SceneManager* yUno_SceneManager::m_loadedScene;

void yUno_SceneManager::SaveSceneData()
{
	// �V�[�������擾
	char* sceneName = const_cast<char*>(typeid(*m_loadedScene).name());
	char* context;
	char* token = strtok_s(sceneName, " ", &context);
	sceneName = strtok_s(NULL, " ", &context);

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
		for (auto objectList : m_loadedScene->m_sceneObject)
		{
			// ���X�g���̃I�u�W�F�N�g�擾
			for (auto object : objectList)
			{
				// ----- �I�u�W�F�N�g�^�C�v�擾���� ----- //
				char tmpObjectType[50];
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
						sprintf_s(writeData, "%f, %f, %f", castComponent.Position.x, castComponent.Position.y, castComponent.Position.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// Rotation�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.Rotation.x, castComponent.Rotation.y, castComponent.Rotation.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// Scale�̒l��������
						sprintf_s(writeData, "%f, %f, %f", castComponent.Scale.x, castComponent.Scale.y, castComponent.Scale.z);
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
	// �V�[�������擾
	char* sceneName = (char*)loadSceneName;
	char usedSceneName[30];
	ZeroMemory(usedSceneName, sizeof(usedSceneName));
	memcpy(usedSceneName, sceneName, strlen(sceneName));
	char* context;
	char* token = strtok_s(usedSceneName, " ", &context);
	sceneName = strtok_s(NULL, " ", &context);

	// �V�[���t�@�C�������擾
	char sceneFileName[30] = { "Assets/" };
	strcat_s(sceneFileName, sizeof(sceneFileName), sceneName);
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
				addedObject = m_loadedScene->LoadSceneObject<SpectatorCamera>(layerNo, objNameData.myName);
			}
			// Test�I�u�W�F�N�g�H
			else if (strcmp(objectType, "Test") == 0)
			{
				addedObject = m_loadedScene->LoadSceneObject<Test>(layerNo, objNameData.myName);
			}
			// Test2�I�u�W�F�N�g�H
			else if (strcmp(objectType, "Test2") == 0)
			{
				addedObject = m_loadedScene->LoadSceneObject<Test2>(layerNo, objNameData.myName);
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
						addedObject->transform->Position = Vector3(x, y, z);
						fscanf_s(file, "%f, %f, %f", &x, &y, &z);
						addedObject->transform->Rotation = Vector3(x, y, z);
						fscanf_s(file, "%f, %f, %f", &x, &y, &z);
						addedObject->transform->Scale = Vector3(x, y, z);
					}
				}
			}
			addedObject = nullptr;
			ZeroMemory(baseName, sizeof(baseName));
		}
		// �t�@�C�������
		fclose(file);
	}
}

void yUno_SceneManager::Delete(GameObject* object)
{
	// �I�u�W�F�N�g�������폜
	yUno_SystemManager::yUno_GameObjectManager::DeleteObjectNameData(object->GetName());

	// ===== �I�u�W�F�N�g�폜�̃��b�Z�[�W�𑗂� ===== //
	// �C���X�^���X����
	MessageData messageData;
	// ������
	messageData.message.header.type = MessageType::ObjectDelete;	// ���b�Z�[�W���
	messageData.message.body.object.SetName(object->GetName());		// �I�u�W�F�N�g��
	// ���b�Z�[�W�𑗂�
	yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendMessageData(messageData);
}

yUno_SceneManager::yUno_SceneManager()
{
	m_loadedScene = nullptr;
	m_sceneName = nullptr;
}

void yUno_SceneManager::InitBase()
{
	// ���݃V�[���̏���������
	Init();
}

void yUno_SceneManager::UnInitBase()
{
	// ���݂̃V�[����Ԃ��Z�[�u
	SaveSceneData();

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_loadedScene->m_sceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->UnInitBase();	// �I������
			delete object;			// �폜
		}
		//���X�g�̃N���A
		objectList.clear();	
	}
	// �}�l�[�W���[�̏I������
	yUno_SystemManager::yUno_GameObjectManager::UnInit();
	// ���݃V�[���̏I������
	m_loadedScene->UnInit();
	delete m_loadedScene;
}

void yUno_SceneManager::UpdateBase()
{
	// Box�^�̓����蔻��p���X�g���쐬
	std::list<BoxCollider*> BoxCollider_List;

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_loadedScene->m_sceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->UpdateBase();	// �X�V����
			
			// "BoxCollider"�R���|�[�l���g���擾
			BoxCollider *boxcol = object->GetComponent<BoxCollider>();
			// �擾�o�����H
			if (boxcol != nullptr)
				BoxCollider_List.push_back(boxcol);	// ���X�g�Ɋi�[���Ă���
		}
	}

	// �����蔻����s���I�u�W�F�N�g���V�[�����ɑ��݂���H
	if (!BoxCollider_List.max_size() >= 2)
	{
		// ���葤�̓����蔻��p���X�g���쐬
		std::list<BoxCollider*> Other_BoxCollider_List = BoxCollider_List;
		// ���葤�̓����蔻��p���X�g�̂O�Ԗځi�n�߂Ɋi�[����Ă�����j���폜����
		// �����g�Ƃ̓����蔻��̏�����j�~���邽��
		Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());

		// ===== "BoxCollider"���m�̓����蔻�� ===== //
		for (auto my_BoxCol : BoxCollider_List)
		{
			// �����蔻���S�ʂ�s�����H
			if (Other_BoxCollider_List.empty())
				break;	// ����I��

			for (auto other_BoxCol : Other_BoxCollider_List)
			{
				my_BoxCol->CalcCollision(other_BoxCol);	// �v�Z����
			}

			// ���葤�̓����蔻��p���X�g�̂O�Ԗځi�n�߂Ɋi�[����Ă�����j���폜����
			// �������蔻����d�����Ĕ��肷�邱�Ƃ�j�~���邽��
			Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());
		}

	}

	// ���݃V�[���̍X�V����
	m_loadedScene->Update();
}


#include "renderer.h"
void yUno_SceneManager::DrawBase()
{
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
	for (auto& objectList : m_loadedScene->m_sceneObject)
	{
		// ���X�g���̃I�u�W�F�N�g�擾
		for (GameObject* object : objectList)
		{
			object->DrawBase(matrix);	// �`�揈��
		}
	}

	// ���݃V�[���̕`�揈��
	m_loadedScene->Draw();
}
