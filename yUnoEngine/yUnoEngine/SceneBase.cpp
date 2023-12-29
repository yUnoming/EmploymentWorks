#include "yUno_NetWorkManager.h"
#include "yUno_GameObjectManager.h"

#include "SceneBase.h"
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
			object->UpdateBase();	// 更新処理
		}
	}
}

void SceneBase::Draw()
{
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_sceneObjectList)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->DrawBase(matrix);	// 描画処理
		}
	}

}
