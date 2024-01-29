#include "SystemNetWorkManager.h"
#include "SystemGameObjectManager.h"
#include "SystemCollisionManager.h"
#include "SystemSceneManager.h"

#include "SceneBase.h"
#include "EditScene.h"
#include "Camera.h"
#include "Message.h"


void Ctlan::PrivateSystem::SceneBase::Delete(GameObject* object)
{
	// オブジェクト名情報を削除
	Ctlan::PrivateSystem::SystemManager::SystemGameObjectManager::DeleteObjectNameData(object->GetName());
	if (object->GetComponent<BoxCollider>())
		Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(object->GetComponent<BoxCollider>());

	// ===== オブジェクト削除のメッセージを送る ===== //
	// インスタンス生成
	MessageData messageData;
	// 情報を代入
	messageData.message.header.type = MessageType::ObjectDelete;	// メッセージ種別
	messageData.message.body.object.SetName(object->GetName());		// オブジェクト名
	// メッセージを送る
	Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->SendMessageData(messageData);
}

Ctlan::PrivateSystem::SceneBase::SceneBase()
{
	ZeroMemory(m_sceneName, sizeof(m_sceneName));
}

void Ctlan::PrivateSystem::SceneBase::Init()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->InitBase();	// 初期化処理
		}
	}
}

void Ctlan::PrivateSystem::SceneBase::Uninit()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->UninitBase();	// 終了処理
			delete object;			// 削除
		}
		//リストのクリア
		objectList.clear();
	}
}

void Ctlan::PrivateSystem::SceneBase::Update()
{
	bool isDestroy;
	std::list<GameObject*> destroyObjectList;

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			// アクティブ状態？
			if (object->isActive)
			{
				isDestroy = object->UpdateBase();	// 更新処理(戻り値で削除フラグ取得)
				
				// オブジェクトを削除する？
				if (isDestroy)
					destroyObjectList.push_back(object);	// 削除用リストに格納
			}
		}
	}

	// 削除するオブジェクトが存在する？
	if (!destroyObjectList.empty())
	{
		// オブジェクト分ループ
		for (GameObject* object : destroyObjectList)
		{
			DeleteSceneObject(object);	// シーンからオブジェクトを削除
		}
	}
}

void Ctlan::PrivateSystem::SceneBase::Draw()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
// デバッグ時の処理
#if _DEBUG
			// デモプレイ中ではない？
			if(!dynamic_cast<EngineScene::EditScene*>(SystemManager::SystemSceneManager::GetEditScene())->IsDemoPlay())
			{
				// カメラコンポーネントを持っている？
				if (object->GetComponent<Camera>())
					continue;	// 次のオブジェクトに遷移
			}

#endif
// 通常の処理
			// アクティブ状態？
			if(object->isActive)
				object->DrawBase();	// 描画処理
		}
	}
}
