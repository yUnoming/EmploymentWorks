// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
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
	int layer;			// レイヤー番号
	GameObject object;	// オブジェクト情報
	int componentNum;	// コンポーネント数
};

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
		// カメラを取得
		auto spectatorCamera = GetSceneObject<SpectatorCamera>();

		// カメラのトランスフォームを代入
		Transform cameraTransform;
		cameraTransform.Position = spectatorCamera->transform->Position;
		cameraTransform.Rotation = spectatorCamera->transform->Rotation;
		cameraTransform.Scale = spectatorCamera->transform->Scale;

		// 書き込み処理
		fwrite(&cameraTransform, sizeof(cameraTransform), 1, file);

		//yUno_SceneManager sceneData = *m_loadedScene;
		//fwrite(&sceneData, sizeof(sceneData), 1, file);

		//int layerNo = 0;	// レイヤー番号
		//// 各スレッド内のオブジェクトリスト取得
		//for (auto& objectList : m_loadedScene->m_sceneObject)
		//{
		//	// リスト内のオブジェクト取得
		//	for (GameObject* object : objectList)
		//	{
		//		GameObject writeObject;
		//		writeObject = *object;
		//		std::list<Component*> componentList = object->GetComponentAll();

		//		SceneObjectData sceneObjectData = { layerNo, writeObject, componentList.size()};
		//		fwrite(&sceneObjectData, sizeof(SceneObjectData), 1, file);

		//		// リスト内のコンポーネントを一つずつ取得
		//		for (auto com : componentList)
		//		{
		//			fwrite(com, sizeof(com), 1, file);
		//		}

		//	}
		//	layerNo++;	// レイヤー番号を進める
		//}

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
	fopen_s(&file, sceneFileName, "rb");

	// 開くことができた？
	if (file)
	{
		// ===== ロード処理 ===== //
		// カメラオブジェクト作成
		Transform* cameraTransform = AddSceneObject<SpectatorCamera>(0)->transform;
		// カメラのトランスフォーム情報を読み取る
		Transform readTransform;
		fread(&readTransform, sizeof(readTransform), 1, file);

		// 読み取った値を代入
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
		// ファイルを閉じる
		fclose(file);
	}

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
		objectList.clear();	//リストのクリア
	}
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

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//ラムダ式
	}

	// 相手側の当たり判定用リストを作成
	std::list<BoxCollider*> Other_BoxCollider_List = BoxCollider_List;
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

		// 当たり判定の相手用リストの０番目（始めに格納されている情報）を削除する
		// ※当たり判定を重複して判定することを阻止するため
		Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());
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
