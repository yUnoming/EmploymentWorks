// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
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

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
std::array<std::list<GameObject*>, 4> yUno_SceneManager::m_sceneObject;
yUno_SceneManager* yUno_SceneManager::m_loadedScene;

void yUno_SceneManager::SaveSceneData()
{
	// シーン名を取得
	char* sceneName = const_cast<char*>(typeid(*m_loadedScene).name());
	char* context;
	char* token = strtok_s(sceneName, " ", &context);
	sceneName = strtok_s(NULL, " ", &context);

	// シーンファイル名を取得
	char sceneFileName[30] = { "Assets\\" };
	strcat_s(sceneFileName, sizeof(sceneFileName), sceneName);
	strcat_s(sceneFileName, sizeof(sceneFileName), ".dat");

	// シーンファイルを開く
	FILE* file;
	fopen_s(&file, sceneFileName, "wb");
	
	// 開くことが出来た？
	if (file)
	{
		// ===== セーブ処理 ===== //
		int layerNo = 0;					// レイヤー番号
		char* objectType = 0;				// オブジェクトタイプ
		char* componentType = 0;			// コンポーネントタイプ
		// 各スレッド内のオブジェクトリスト取得
		for (auto objectList : m_loadedScene->m_sceneObject)
		{
			// リスト内のオブジェクト取得
			for (auto object : objectList)
			{
				// ----- オブジェクトタイプ取得処理 ----- //
				char tmpObjectType[50];
				objectType = const_cast<char*>(typeid(*object).name());
				ZeroMemory(tmpObjectType, sizeof(tmpObjectType));
				memcpy(tmpObjectType, objectType, strlen(objectType));
				token = strtok_s(tmpObjectType, " ", &context);
				objectType = strtok_s(NULL, " ", &context);

				// ----- オブジェクト名情報取得 ----- //
				const char* name = object->GetName();
				yUno_SystemManager::yUno_GameObjectManager::ObjectNameData
					objNameData = yUno_SystemManager::yUno_GameObjectManager::GetObjectNameData(name);

				// 書き込み処理
				char writeData[100] = {};
				sprintf_s(writeData, "%d %s %s %d", layerNo, objectType, objNameData.baseName, objNameData.number);
				fprintf(file, writeData);
				fprintf(file, "\r\n");

				// 現在取得しているオブジェクトのコンポーネントを全取得
				std::list<Component*> componentList = object->GetComponentAll();

				int componentNum = componentList.size();
				char componentNumData[2] = {};
				sprintf_s(componentNumData, "%d", componentNum);
				fprintf(file, componentNumData);
				fprintf(file, "\r\n");

				// リスト内のコンポーネント取得
				for (auto* component : componentList)
				{
					// ----- コンポーネントタイプ取得処理 ----- //
					char tmpComponentType[50];
					componentType = const_cast<char*>(typeid(*component).name());
					ZeroMemory(tmpComponentType, sizeof(tmpComponentType));
					memcpy(tmpComponentType, componentType, strlen(componentType));
					token = strtok_s(tmpComponentType, " ", &context);
					componentType = strtok_s(NULL, " ", &context);
					
					// 書き込み処理
					fprintf(file, componentType);
					fprintf(file, "\r\n");

					// Transformコンポーネント？
					if (strcmp(componentType, "PublicSystem::Transform") == 0)
					{
						// 欲しい型に直す
						Transform castComponent = *dynamic_cast<Transform*>(component);

						// Positionの値書き込み
						sprintf_s(writeData, "%f, %f, %f", castComponent.Position.x, castComponent.Position.y, castComponent.Position.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// Rotationの値書き込み
						sprintf_s(writeData, "%f, %f, %f", castComponent.Rotation.x, castComponent.Rotation.y, castComponent.Rotation.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// Scaleの値書き込み
						sprintf_s(writeData, "%f, %f, %f", castComponent.Scale.x, castComponent.Scale.y, castComponent.Scale.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");
					}
				}
			}
			layerNo++;	// レイヤー番号を進める
		}

		// ファイルを閉じる
		fclose(file);
	}
}

void yUno_SceneManager::LoadSceneData(const char* loadSceneName)
{
	// シーン名を取得
	char* sceneName = (char*)loadSceneName;
	char usedSceneName[30];
	ZeroMemory(usedSceneName, sizeof(usedSceneName));
	memcpy(usedSceneName, sceneName, strlen(sceneName));
	char* context;
	char* token = strtok_s(usedSceneName, " ", &context);
	sceneName = strtok_s(NULL, " ", &context);

	// シーンファイル名を取得
	char sceneFileName[30] = { "Assets/" };
	strcat_s(sceneFileName, sizeof(sceneFileName), sceneName);
	strcat_s(sceneFileName, sizeof(sceneFileName), ".dat");

	// シーンファイルを開く
	FILE* file;
	fopen_s(&file, sceneFileName, "r");

	// 開くことができた？
	if (file)
	{
		// ===== ロード処理 ===== //
		int layerNo = 0;
		char objectType[100] = { 0 };
		char baseName[100] = { 0 };
		int number = 0;

		// 読み込むオブジェクトが無くなるまでループ
		while (fscanf_s(file, "%d %s %s %d", &layerNo, objectType, (unsigned int)sizeof(objectType),
			&baseName, (unsigned int)sizeof(baseName), &number) != EOF)
		{
			// 追加したオブジェクト
			GameObject* addedObject = 0;

			// ----- オブジェクト名情報を設定 ----- //
			yUno_SystemManager::yUno_GameObjectManager::ObjectNameData objNameData;
			strcpy_s(objNameData.baseName, baseName);					// 番号を付与する前の名前
			objNameData.number = number;								// オブジェクト番号
			// オブジェクト番号が０番？
			if (number == 0) {
				strcpy_s(objNameData.myName, baseName);					// 元の名称のまま
			}
			else {
				sprintf_s(objNameData.myName, "%s%d", baseName, number);// 元の名称に番号を付与する
			}
			yUno_SystemManager::yUno_GameObjectManager::SetObjectNameData(objNameData);

			// ----- オブジェクトの追加処理 ----- //
			// SpectatorCameraオブジェクト？
			if (strcmp(objectType, "SpectatorCamera") == 0)
			{
				// オブジェクト追加
				addedObject = m_loadedScene->LoadSceneObject<SpectatorCamera>(layerNo, objNameData.myName);
			}
			// Testオブジェクト？
			else if (strcmp(objectType, "Test") == 0)
			{
				addedObject = m_loadedScene->LoadSceneObject<Test>(layerNo, objNameData.myName);
			}
			// Test2オブジェクト？
			else if (strcmp(objectType, "Test2") == 0)
			{
				addedObject = m_loadedScene->LoadSceneObject<Test2>(layerNo, objNameData.myName);
			}

			if (addedObject != nullptr)
			{
				// ----- コンポーネントの追加処理 ----- //
				// コンポーネント数読み取り
				int componentNum = 0;
				fscanf_s(file, "%d", &componentNum);

				// コンポーネント数だけループ
				for (int i = 0; i < componentNum; i++)
				{
					// コンポーネントタイプ取得
					char componentType[100] = { 0 };
					fscanf_s(file, "%s", &componentType, (unsigned int)sizeof(componentType));

					// Transformコンポーネント？
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
		// ファイルを閉じる
		fclose(file);
	}
}

void yUno_SceneManager::Delete(GameObject* object)
{
	// オブジェクト名情報を削除
	yUno_SystemManager::yUno_GameObjectManager::DeleteObjectNameData(object->GetName());

	// ===== オブジェクト削除のメッセージを送る ===== //
	// インスタンス生成
	MessageData messageData;
	// 情報を代入
	messageData.message.header.type = MessageType::ObjectDelete;	// メッセージ種別
	messageData.message.body.object.SetName(object->GetName());		// オブジェクト名
	// メッセージを送る
	yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendMessageData(messageData);
}

yUno_SceneManager::yUno_SceneManager()
{
	m_loadedScene = nullptr;
	m_sceneName = nullptr;
}

void yUno_SceneManager::InitBase()
{
	// 現在シーンの初期化処理
	Init();
}

void yUno_SceneManager::UnInitBase()
{
	// 現在のシーン状態をセーブ
	SaveSceneData();

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_loadedScene->m_sceneObject)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->UnInitBase();	// 終了処理
			delete object;			// 削除
		}
		//リストのクリア
		objectList.clear();	
	}
	// マネージャーの終了処理
	yUno_SystemManager::yUno_GameObjectManager::UnInit();
	// 現在シーンの終了処理
	m_loadedScene->UnInit();
	delete m_loadedScene;
}

void yUno_SceneManager::UpdateBase()
{
	// Box型の当たり判定用リストを作成
	std::list<BoxCollider*> BoxCollider_List;

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_loadedScene->m_sceneObject)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->UpdateBase();	// 更新処理
			
			// "BoxCollider"コンポーネントを取得
			BoxCollider *boxcol = object->GetComponent<BoxCollider>();
			// 取得出来た？
			if (boxcol != nullptr)
				BoxCollider_List.push_back(boxcol);	// リストに格納しておく
		}
	}

	// 当たり判定を行うオブジェクトがシーン内に存在する？
	if (!BoxCollider_List.max_size() >= 2)
	{
		// 相手側の当たり判定用リストを作成
		std::list<BoxCollider*> Other_BoxCollider_List = BoxCollider_List;
		// 相手側の当たり判定用リストの０番目（始めに格納されている情報）を削除する
		// ※自身との当たり判定の処理を阻止するため
		Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());

		// ===== "BoxCollider"同士の当たり判定 ===== //
		for (auto my_BoxCol : BoxCollider_List)
		{
			// 当たり判定を全通り行った？
			if (Other_BoxCollider_List.empty())
				break;	// 判定終了

			for (auto other_BoxCol : Other_BoxCollider_List)
			{
				my_BoxCol->CalcCollision(other_BoxCol);	// 計算処理
			}

			// 相手側の当たり判定用リストの０番目（始めに格納されている情報）を削除する
			// ※当たり判定を重複して判定することを阻止するため
			Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());
		}

	}

	// 現在シーンの更新処理
	m_loadedScene->Update();
}


#include "renderer.h"
void yUno_SceneManager::DrawBase()
{
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_loadedScene->m_sceneObject)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->DrawBase(matrix);	// 描画処理
		}
	}

	// 現在シーンの描画処理
	m_loadedScene->Draw();
}
