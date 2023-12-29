// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_NetWorkManager.h"
#include "SpectatorCamera.h"
#include "Transform.h"
#include "Camera.h"

#include "KeyInput.h"
#include "InputPartsName.h"
#include "MouseInput.h"
#include "ScreenInput.h"
#include "Material.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		  using宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace PublicSystem;


void SpectatorCamera::Init()
{
	// コンポーネント追加
	AddComponent<Camera>();
}

void SpectatorCamera::Update()
{
	// ===== 自身の操作 ===== //
	if (KeyInput::GetKeyDown(UpArrow))
		transform->position.y += 0.01f;
	if (KeyInput::GetKeyDown(LeftArrow))
		transform->position.x -= 0.01f;
	if (KeyInput::GetKeyDown(DownArrow))
		transform->position.y -= 0.01f;
	if (KeyInput::GetKeyDown(RightArrow))
		transform->position.x += 0.01f;

	// ===== 視野角の縮小・拡大 ===== //
	//if (MouseInput::GetWheelRotation_Forward())
	//{
	//	GetComponent<Camera>()->FieldOfView -= 0.5f;
	//}
	//else if (MouseInput::GetWheelRotation_Backward())
	//{
	//	GetComponent<Camera>()->FieldOfView += 0.5f;
	//}

	// ===== クリックしたオブジェクトを取得 ===== //
	// 左クリックされた？
	if (MouseInput::GetMouseDownTrigger(LeftButton))
	{
		// クリックしたオブジェクトを一時的に代入する変数
		GameObject* tmpClickedObject;

		// クリックした位置にオブジェクトがある場合、そのオブジェクトを取得
		// 取得された状態でオブジェクトがない場所がクリックされたら、取得を解除する
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		
		// クリックされたオブジェクトがロックされていたら処理を終了
		if (tmpClickedObject && yUno_SystemManager::yUno_NetWorkManager::GetServer()->IsRockObject(tmpClickedObject->GetName()))
			return;

		// ----- 現在のクリック状態によって処理を分岐 ----- //
		// 別のオブジェクトがクリックされた？
		if (tmpClickedObject && m_clickedObject && tmpClickedObject != m_clickedObject)
		{
			// クリックされたオブジェクトをメンバ変数に代入
			m_clickedObject = tmpClickedObject;

			// ----- 送信する値を代入 ----- //
			// インスタンス生成
			MessageData messageData;
			// メッセージタイプ
			messageData.message.header.type = MessageType::ClickObject;
			// オブジェクト
			messageData.message.body.object.CopyName(m_clickedObject->GetName());
			
			// メッセージを送る処理を実行
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
		// オブジェクトがクリックされた？
		else if (tmpClickedObject)
		{
			// クリックされたオブジェクトをメンバ変数に代入
			m_clickedObject = tmpClickedObject;

			// ----- 送信する値を代入 ----- //
			// インスタンス生成
			MessageData messageData;
			// メッセージタイプ
			messageData.message.header.type = MessageType::ClickObject;
			// オブジェクト
			messageData.message.body.object.CopyName(m_clickedObject->GetName());

			// メッセージを送る処理を実行
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
		// オブジェクトが解除された？
		else if (!tmpClickedObject && m_clickedObject)
		{
			// クリックオブジェクトを解除
			m_clickedObject = nullptr;

			// ----- 送信する値を代入 ----- //
			// インスタンス生成
			MessageData messageData;
			// メッセージタイプ
			messageData.message.header.type = MessageType::ClickObject;
			// オブジェクト
			messageData.message.body.object.CopyName(nullptr);

			// メッセージを送る処理を実行
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->
				SendMessageData(messageData);
		}
	}

	// ===== クリックしたオブジェクトの操作 ===== //
	// オブジェクトを取得している？
	if (m_clickedObject)
	{
		if (KeyInput::GetKeyDown(W))
			m_clickedObject->transform->position.z += 0.01f;
		if (KeyInput::GetKeyDown(A))
			m_clickedObject->transform->position.x -= 0.01f;
		if (KeyInput::GetKeyDown(S))
			m_clickedObject->transform->position.z -= 0.01f;
		if (KeyInput::GetKeyDown(D))
			m_clickedObject->transform->position.x += 0.01f;
	}	
}

GameObject* SpectatorCamera::GetClickedObject() const
{
	return m_clickedObject;
}
