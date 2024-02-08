// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
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

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   staticメンバ変数の定義        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
Ctlan::PrivateSystem::SceneBase* Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_loadedScene;
Ctlan::PrivateSystem::SceneBase* Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_editScene;
std::unordered_map<std::string, Ctlan::PrivateSystem::SceneBase*> Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_scenePool;
Ctlan::PrivateSystem::Information::LaunchSceneInformation Ctlan::PrivateSystem::SystemManager::SystemSceneManager::m_launchSceneInfo;
bool Ctlan::PrivateSystem::SystemManager::SystemSceneManager::isSave;
char Ctlan::PrivateSystem::SystemManager::SystemSceneManager::loadSceneName[30];

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::SaveSceneData()
{
	// シーン名を取得
	char* sceneName = m_loadedScene->GetSceneName();

	// シーンファイル名を取得
	char sceneFileName[30] = { "Assets/Scenes/" };
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

				// ----- オブジェクト名情報取得 ----- //
				const char* name = object->GetName();
				Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData
					objNameData = Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::GetObjectNameData(name);

				// 書き込み処理
				char writeData[100] = {};
				sprintf_s(writeData, "%d %s %s %d", layerNo, objectType, objNameData.baseName, objNameData.number);
				fprintf(file, writeData);
				fprintf(file, "\r\n");

				// 現在取得しているオブジェクトのコンポーネントを全取得
				std::list<Component*> componentList = object->GetComponentAll();

				int componentNum = static_cast<int>(componentList.size());
				char componentNumData[2] = {};
				sprintf_s(componentNumData, "%d", componentNum);
				fprintf(file, componentNumData);
				fprintf(file, "\r\n");

				// リスト内のコンポーネント取得
				for (auto* component : componentList)
				{
					// ----- コンポーネントタイプ取得処理 ----- //
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
					
					// 書き込み処理
					fprintf(file, componentType);
					fprintf(file, "\r\n");

					// Transformコンポーネント？
					if (strcmp(componentType, "Transform") == 0)
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
					else if (strcmp(componentType, "Text") == 0)
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
					else if (strcmp(componentType, "SceneLoader") == 0)
					{
						SceneLoader castSceneLoader = *dynamic_cast<SceneLoader*>(component);
						sprintf_s(writeData, "%s", castSceneLoader.loadSceneName);
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

Ctlan::PrivateSystem::SceneBase* Ctlan::PrivateSystem::SystemManager::SystemSceneManager::LoadSceneData(const char* loadSceneName)
{
	// ベースシーンの生成
	SceneBase* loadScene = new SceneBase(loadSceneName);
	// ロードしたシーンを代入
	m_loadedScene = loadScene;

	// シーンファイル名を取得
	char sceneFileName[100] = {"Assets/Scenes/"};
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
			PrivateSystem::GameObject* addedObject = 0;

			// ----- オブジェクト名情報を設定 ----- //
			Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::ObjectNameData objNameData;
			strcpy_s(objNameData.baseName, baseName);					// 番号を付与する前の名前
			objNameData.number = number;								// オブジェクト番号
			// オブジェクト番号が０番？
			if (number == 0) {
				strcpy_s(objNameData.myName, baseName);					// 元の名称のまま
			}
			else {
				sprintf_s(objNameData.myName, "%s%d", baseName, number);// 元の名称に番号を付与する
			}
			Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::SetObjectNameData(objNameData);

			// ----- オブジェクトの追加処理 ----- //
			// TemplateCubeオブジェクト？
			if (strcmp(objectType, "TemplateCube") == 0)
			{
				addedObject = loadScene->LoadSceneObject<EngineObject::TemplateCube>(layerNo, objNameData.myName);
			}
			// TemplateTextオブジェクト？
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
		// ファイルを閉じる
		fclose(file);
	}
	else
		return nullptr;

	m_scenePool[loadSceneName] = loadScene;		// ロードしたシーンを格納
	return loadScene;
}

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::LoadScene()
{
	// 開始シーンのロード？
	if (!m_loadedScene)
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
	}
	else
	{
		// 既にシーンがロードされている？
		if (m_scenePool.count(loadSceneName) > 0 && (m_editScene && !dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay()))
		{
			m_loadedScene = m_scenePool[std::string(loadSceneName)];	// シーンを変更する
			ZeroMemory(loadSceneName, sizeof(loadSceneName));
			return;
		}
		// シーンがロードされていない
		else
		{
			// 現在シーンの終了処理
			m_loadedScene->Uninit();

			// ロードするシーンが存在しない？
			if (LoadSceneData(loadSceneName) == nullptr)
			{
				// システム通知を表示
				MessageBoxW(NULL, L"シーンが存在しませんでした", L"エラーメッセージ", MB_OK);
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
// デバッグ時
#if _DEBUG
	// エディットシーンのロード
	m_editScene = new Ctlan::EngineScene::EditScene();
	m_editScene->Init();
#endif	
// 通常処理
	// 初期シーンのロード
	LoadScene();
	m_loadedScene->Init();
}

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::UninitScene()
{
// デバッグ時
#if _DEBUG
	// エディットシーンの終了処理
	static_cast<EngineScene::EditScene*>(m_editScene)->Uninit(isSave);

	// セーブする？
	if (isSave)
	{
		// 現在のシーン状態をセーブ
		SaveSceneData();
		// 起動するシーン情報をセーブ
		m_launchSceneInfo.Save();
	}

	// マネージャーの終了処理
	SystemManager::SystemGameObjectManager::Uninit();
	delete[] m_editScene;
#endif
// 通常時
	// 現在シーンの終了処理
	m_loadedScene->Uninit();
	delete[] m_loadedScene;
}

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::UpdateScene()
{
#if _DEBUG
	// 現状のデモプレイ状態を保存
	bool lateIsDemoPlay = dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay();
	// エディットシーンの更新処理
	m_editScene->Update();

	// デモプレイが開始された？
	if (!lateIsDemoPlay && dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay())
	{
		// シーンのセーブ
		SaveSceneData();
		// ロードするシーン名を保存
		strcpy_s(loadSceneName, m_loadedScene->GetSceneName());
		// シーンをリロード
		LoadScene();
	}
	// デモプレイが終了した？
	else if (lateIsDemoPlay && !dynamic_cast<EngineScene::EditScene*>(m_editScene)->IsDemoPlay())
	{
		// シーンをリロード
		LoadSceneData(m_launchSceneInfo.GetLaunchSceneName());
		ZeroMemory(loadSceneName, sizeof(loadSceneName));
	}
#endif
	// 現在シーンの更新処理
	m_loadedScene->Update();
	if (strlen(loadSceneName) > 0)
		LoadScene();
}


#include "renderer.h"
void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::DrawScene()
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

void Ctlan::PrivateSystem::SystemManager::SystemSceneManager::CreateNewScene(const char* sceneName)
{
	// 新規シーン生成
	SceneBase* newScene = new SceneBase(sceneName);
	// シーンにカメラ追加
	GameObject* camera = newScene->AddSceneObject<GameObject>(0, "MainCamera");
	camera->AddComponent<Camera>();

	m_scenePool[sceneName] = newScene;		// ロードしたシーンを格納
	m_loadedScene = newScene;				// ロードしたシーンを代入
}
