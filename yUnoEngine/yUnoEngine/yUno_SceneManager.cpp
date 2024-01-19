// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_NetWorkManager.h"
#include "yUno_GameObjectManager.h"

#include "Message.h"
#include "yUno_SceneManager.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Text.h"
#include "SpectatorCamera.h"

#include "TemplateCube.h"
#include "TemplateText.h"

#include "MeteorPool.h"
#include "ParticlePool.h"

#include "EditScene.h"

#include <SimpleMath.h>

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
SceneBase* yUno_SceneManager::m_loadedScene;
SceneBase* yUno_SceneManager::m_editScene;
std::unordered_map<std::string, SceneBase*> yUno_SceneManager::m_scenePool;
yUnoEngine::Information::LaunchSceneInformation yUno_SceneManager::m_launchSceneInfo;

void yUno_SceneManager::SaveSceneData()
{
	// シーン名を取得
	char* sceneName = m_loadedScene->GetSceneName();

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
		for (auto objectList : m_loadedScene->GetAllSceneObjects())
		{
			// リスト内のオブジェクト取得
			for (GameObject* object : objectList)
			{
				Meteor* meteor = (Meteor*)object;
				if (strcmp(typeid(*meteor).name(), "class Meteor") == 0)
					continue;
				Particle* particle = (Particle*)object;
				if (strcmp(typeid(*particle).name(), "class Particle") == 0)
					continue;

				// ----- オブジェクトタイプ取得処理 ----- //
				char tmpObjectType[50];
				char* token;
				char* context;
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
						// 型変換
						Transform castComponent = *dynamic_cast<Transform*>(component);

						// positionの値書き込み
						sprintf_s(writeData, "%f, %f, %f", castComponent.position.x, castComponent.position.y, castComponent.position.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// rotationの値書き込み
						sprintf_s(writeData, "%f, %f, %f", castComponent.rotation.x, castComponent.rotation.y, castComponent.rotation.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");

						// scaleの値書き込み
						sprintf_s(writeData, "%f, %f, %f", castComponent.scale.x, castComponent.scale.y, castComponent.scale.z);
						fprintf(file, writeData);
						fprintf(file, "\r\n");
					}
					// Textコンポーネント？
					else if (strcmp(componentType, "PublicSystem::Text") == 0)
					{
						// 型変換
						Text castComponent = *dynamic_cast<Text*>(component);
						// textの値書き込み
						sprintf_s(writeData, "%s %s", castComponent.text, "textend");
						fprintf(file, writeData);
						fprintf(file, "\r\n");
						// fontSizeの値書き込み
						sprintf_s(writeData, "%f, %f", castComponent.fontSize.x, castComponent.fontSize.y);
						fprintf(file, writeData);
						fprintf(file, "\r\n");
						// leftTopPointの値書き込み
						sprintf_s(writeData, "%f, %f", castComponent.leftTopPoint.x, castComponent.leftTopPoint.y);
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

SceneBase* yUno_SceneManager::LoadSceneData(const char* loadSceneName)
{
	// ベースシーンの生成
	SceneBase* loadScene = new SceneBase(loadSceneName);
	// ロードしたシーンを代入
	m_loadedScene = loadScene;

	// シーンファイル名を取得
	char sceneFileName[30] = { "Assets/" };
	strcat_s(sceneFileName, sizeof(sceneFileName), loadSceneName);
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
			// TemplateCubeオブジェクト？
			if (strcmp(objectType, "EngineObject::TemplateCube") == 0)
			{
				addedObject = loadScene->LoadSceneObject<EngineObject::TemplateCube>(layerNo, objNameData.myName);
			}
			// TemplateTextオブジェクト？
			else if (strcmp(objectType, "EngineObject::TemplateText") == 0)
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
			// それ以外
			else
			{
				addedObject = loadScene->LoadSceneObject<GameObject>(layerNo, objNameData.myName);
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
						addedObject->transform->position = Vector3(x, y, z);
						fscanf_s(file, "%f, %f, %f", &x, &y, &z);
						addedObject->transform->rotation = Vector3(x, y, z);
						fscanf_s(file, "%f, %f, %f", &x, &y, &z);
						addedObject->transform->scale = Vector3(x, y, z);
					}
					else if (strcmp(componentType, "PublicSystem::Text") == 0)
					{
						char text[101];		// 実際のテキスト用変数
						char readText[101];	// 読み取り用テキスト変数
						bool isCatText = false;
						Vector2 fontSize;
						Vector2 leftTopPoint;
						while (true)
						{
							fscanf_s(file, "%s", &readText, 101);

							// テキスト終了？
							if (strcmp(readText, "textend") == 0)
							{
								break;	// ループを抜ける
							}

							// テキストを連結する？
							if (isCatText)
							{
								strcat_s(text, " ");		// 空白の追加
								strcat_s(text, readText);	// 実際のテキスト用変数に連結
							}
							else
							{
								strcpy_s(text, readText);	// 実際のテキスト用変数に連結
								isCatText = true;			// 次回から連結するようにする
							}
						}
						fscanf_s(file, "%f, %f", &fontSize.x, &fontSize.y);
						fscanf_s(file, "%f, %f", &leftTopPoint.x, &leftTopPoint.y);

						if (!addedObject->GetComponent<PublicSystem::Text>())
							addedObject->AddComponent<PublicSystem::Text>();
						
						Text* textCom = addedObject->GetComponent<PublicSystem::Text>();
						textCom->ChangeText(text);
						textCom->fontSize = fontSize;
						textCom->leftTopPoint = leftTopPoint;
					}
					else if (strcmp(componentType, "PublicSystem::Camera") == 0)
					{
						if (!addedObject->GetComponent<PublicSystem::Camera>())
							addedObject->AddComponent<PublicSystem::Camera>();
					}
				}
			}
			addedObject = nullptr;
			ZeroMemory(baseName, sizeof(baseName));
		}
		// ファイルを閉じる
		fclose(file);
	}
	else
		return nullptr;

	m_scenePool[loadSceneName] = loadScene;		// ロードしたシーンを格納
	return loadScene;
}

void yUno_SceneManager::LoadScene()
{
	// 起動するシーン情報をロード
	m_launchSceneInfo.Load();

	// 起動するシーンが存在しない？
	if (!m_launchSceneInfo.GetLaunchSceneName())
		// 初期シーン作成
		CreateNewScene("SampleScene");
	// 起動するシーンが存在する
	else
		// 起動時に開くシーンをロード
		LoadSceneData(m_launchSceneInfo.GetLaunchSceneName());
	
	// ロードしたシーンの初期化
	m_loadedScene->Init();
}

yUno_SceneManager::yUno_SceneManager()
{
	m_loadedScene = nullptr;
}

#include "MeteorPool.h"
#include "ParticlePool.h"
void yUno_SceneManager::InitScene()
{
#if _DEBUG
	// エディットシーンのロード
	m_editScene = new yUnoEngine::EditScene();
	m_editScene->Init();
#endif	
	// 初期シーンのロード
	LoadScene();
	//m_loadedScene->AddSceneObject<Meteor>(1, "Meteor");
	//m_loadedScene->AddSceneObject<Meteor>(1, "Meteor");
	//m_loadedScene->AddSceneObject<Meteor>(1, "Meteor");
	//m_loadedScene->AddSceneObject<Meteor>(1, "Meteor");
	//m_loadedScene->AddSceneObject<Meteor>(1, "Meteor");
	//Text* textCom = m_loadedScene->AddSceneObject<Test2>(3, "Text")->GetComponent<Text>();
	//textCom->text = "Press Any Key";
}

void yUno_SceneManager::UninitScene()
{
#if _DEBUG
	// エディットシーンの終了処理
	m_editScene->Uninit();
	// 現在のシーン状態をセーブ
	SaveSceneData();
	// 起動するシーン情報をセーブ
	m_launchSceneInfo.Save();

	// マネージャーの終了処理
	yUno_SystemManager::yUno_GameObjectManager::Uninit();
#endif
	// 現在シーンの終了処理
	m_loadedScene->Uninit();
	delete m_loadedScene;
}

void yUno_SceneManager::UpdateScene()
{
#if _DEBUG
	// エディットシーンの更新処理
	m_editScene->Update();
#endif
	// 現在シーンの更新処理
	m_loadedScene->Update();
}


#include "renderer.h"
void yUno_SceneManager::DrawScene()
{
	// 現在シーンの描画処理
	m_loadedScene->Draw();
#if _DEBUG
	// クリアすることでマニピュレーターをオブジェクトに被せて描画させている
	Renderer::ClearDepthStencilView();
	// エディットシーンの描画処理
	m_editScene->Draw();
#endif
}

void yUno_SceneManager::CreateNewScene(const char* sceneName)
{
	// 新規シーン生成
	SceneBase* newScene = new SceneBase(sceneName);
	// シーンにカメラ追加
	GameObject* camera = newScene->AddSceneObject<GameObject>(0, "MainCamera");
	camera->AddComponent<Camera>();

	m_scenePool[sceneName] = newScene;		// ロードしたシーンを格納
	m_loadedScene = newScene;				// ロードしたシーンを代入
}
