#include "yUno_NetWorkManager.h"
#include "yUno_GameObjectManager.h"

#include "SceneBase.h"
#include "Camera.h"
#include "Message.h"


void SceneBase::Delete(GameObject* object)
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

SceneBase::SceneBase()
{
	ZeroMemory(m_sceneName, sizeof(m_sceneName));
}

void SceneBase::UnInit()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
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
}

void SceneBase::Update()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			// アクティブ状態？
			if(object->isActive)
				object->UpdateBase();	// 更新処理
		}
	}
}

void SceneBase::Draw()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
// デバッグ時の処理
#if _DEBUG
			// カメラコンポーネントを持っている？
			if (object->GetComponent<Camera>())
				continue;	// 次のオブジェクトに遷移
#endif
// 通常の処理
			// アクティブ状態？
			if(object->isActive)
				object->DrawBase();	// 描画処理
		}
	}

}
