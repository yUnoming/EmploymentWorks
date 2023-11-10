// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_SceneManager.h"
#include "SampleScene.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "SpectatorCamera.h"

#include <SimpleMath.h>

std::array<std::list<GameObject*>, 4> yUno_SceneManager::m_sceneObject;

struct SceneObjectData
{
	int layer;			// ���C���[�ԍ�
	GameObject object;	// �I�u�W�F�N�g���
	int componentNum;	// �R���|�[�l���g��
};

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
		// �J�������擾
		auto spectatorCamera = GetSceneObject<SpectatorCamera>();

		// �J�����̃g�����X�t�H�[������
		Transform cameraTransform;
		cameraTransform.Position = spectatorCamera->transform->Position;
		cameraTransform.Rotation = spectatorCamera->transform->Rotation;
		cameraTransform.Scale = spectatorCamera->transform->Scale;

		// �������ݏ���
		fwrite(&cameraTransform, sizeof(cameraTransform), 1, file);

		//yUno_SceneManager sceneData = *m_loadedScene;
		//fwrite(&sceneData, sizeof(sceneData), 1, file);

		//int layerNo = 0;	// ���C���[�ԍ�
		//// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
		//for (auto& objectList : m_loadedScene->m_sceneObject)
		//{
		//	// ���X�g���̃I�u�W�F�N�g�擾
		//	for (GameObject* object : objectList)
		//	{
		//		GameObject writeObject;
		//		writeObject = *object;
		//		std::list<Component*> componentList = object->GetComponentAll();

		//		SceneObjectData sceneObjectData = { layerNo, writeObject, componentList.size()};
		//		fwrite(&sceneObjectData, sizeof(SceneObjectData), 1, file);

		//		// ���X�g���̃R���|�[�l���g������擾
		//		for (auto com : componentList)
		//		{
		//			fwrite(com, sizeof(com), 1, file);
		//		}

		//	}
		//	layerNo++;	// ���C���[�ԍ���i�߂�
		//}

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
	fopen_s(&file, sceneFileName, "rb");

	// �J�����Ƃ��ł����H
	if (file)
	{
		// ===== ���[�h���� ===== //
		// �J�����I�u�W�F�N�g�쐬
		Transform* cameraTransform = AddSceneObject<SpectatorCamera>(0)->transform;
		// �J�����̃g�����X�t�H�[������ǂݎ��
		Transform readTransform;
		fread(&readTransform, sizeof(readTransform), 1, file);

		// �ǂݎ�����l����
		cameraTransform->Position = readTransform.Position;
		cameraTransform->Rotation = readTransform.Rotation;
		cameraTransform->Scale = readTransform.Scale;


	//	//while (true)
	//	//{
	//	//	SceneObjectData sceneObjectData;
	//	//	int readNum = fread(&sceneObjectData, sizeof(SceneObjectData), 1, file);

	//	//	if (readNum != 0)
	//	//	{
	//	//		//m_loadedScene->m_sceneObject[sceneObjectData.layer].push_back(&sceneObjectData.object);
	//	//	}
	//	//	else
	//	//		break;
	//	//}
		// �t�@�C�������
		fclose(file);
	}

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
		objectList.clear();	//���X�g�̃N���A
	}
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

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//�����_��
	}

	// ���葤�̓����蔻��p���X�g���쐬
	std::list<BoxCollider*> Other_BoxCollider_List = BoxCollider_List;
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

		// �����蔻��̑���p���X�g�̂O�Ԗځi�n�߂Ɋi�[����Ă�����j���폜����
		// �������蔻����d�����Ĕ��肷�邱�Ƃ�j�~���邽��
		Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());
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
