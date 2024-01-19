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


void EngineObject::SpectatorCamera::Init()
{
	// コンポーネント追加
	AddComponent<Camera>();
}

void EngineObject::SpectatorCamera::Update()
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

	// ===== クリックしたオブジェクトを取得 ===== //
	static bool isTextMove = false;
	bool isObjectClicked = false;	// オブジェクトがクリックされたかどうか
	// 左クリックされた？
	if (MouseInput::GetMouseDownTrigger(LeftButton))
	{
		// クリックしたオブジェクトを一時的に代入する変数
		GameObject* tmpClickedObject;

		// エディットシーンを参照して、クリックされたオブジェクトを取得
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointManipulator(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		// オブジェクトがクリックされた？
		if (tmpClickedObject)
		{
			m_clickedManipulator = tmpClickedObject;	// クリックされたオブジェクトを代入
			return;	// 更新処理終了
		}

		// 現在のシーンを参照して、クリックされたオブジェクトを取得
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		// クリックされたオブジェクトがロックされていたら処理を終了
		if (tmpClickedObject && yUno_SystemManager::yUno_NetWorkManager::GetServer()->IsRockObject(tmpClickedObject->GetName()))
			return;

		// ----- 現在のクリック状態によって処理を分岐 ----- //
		// 別のオブジェクトがクリックされた？
		if (tmpClickedObject && m_clickedObject && tmpClickedObject != m_clickedObject)
		{
			// テキストコンポーネントを持っている？
			if (m_clickedObject->GetComponent<Text>())
			{
				// テキストが入っていない状態で解除された？
				if (strcmp(m_clickedObject->GetComponent<Text>()->text, "") == 0)
					m_clickedObject->Destroy();	// 削除
			}

			// クリックされたオブジェクトをメンバ変数に代入
			m_clickedObject = tmpClickedObject;
			// クリックされたことを伝える
			isObjectClicked = true;

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
			// クリックされたことを伝える
			isObjectClicked = true;

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
			// テキストコンポーネントを持っている？
			if (m_clickedObject->GetComponent<Text>())
			{
				// テキストが入っていない状態で解除された？
				if (strcmp(m_clickedObject->GetComponent<Text>()->text, "") == 0)
					m_clickedObject->Destroy();	// 削除
			}

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
	// テキストオブジェクトが離された？
	else if (MouseInput::GetMouseUp(LeftButton) && m_clickedObject && m_clickedObject->GetComponent<Text>())
	{
		// テキスト移動を実行できないようにする
		isTextMove = false;
	}
	// マニピュレーターが離された？
	else if (MouseInput::GetMouseUp(LeftButton) && m_clickedManipulator)
	{
		m_clickedManipulator = nullptr;
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

		// テキストコンポーネントを持っている？
		if (m_clickedObject->GetComponent<Text>())
		{
			// ===== テキスト移動処理 ===== //
			static Vector2 startCursorPosition;		// 処理開始時のクリック座標 
			static Vector2 startLeftTopPoint;		// 処理開始時の左上座標
			// 現在のカーソル座標
			Vector2 nowCursorPosition = MouseInput::GetCursorPosition();

			// テキストがクリックされた瞬間？
			if (isObjectClicked)
			{
				// 開始時に取得する情報を取得
				isTextMove = true;
				startCursorPosition = nowCursorPosition;
				startLeftTopPoint = m_clickedObject->GetComponent<Text>()->leftTopPoint;
			}
			// テキスト移動処理が実行できる？
			else if(isTextMove)
			{
				// テキストの左上座標を計算
				m_clickedObject->GetComponent<Text>()->leftTopPoint = startLeftTopPoint + (nowCursorPosition - startCursorPosition);
			}

			// ===== テキストのフォントサイズの拡大・縮小 ===== //
			// マウスホイールが前方回転された？
			if (MouseInput::GetWheelRotationForward())
			{
				// フォントサイズを拡大する
				m_clickedObject->GetComponent<Text>()->fontSize *= 1.1f;
			}
			// マウスホイールが後方回転された？
			else if (MouseInput::GetWheelRotationBackward())
			{
				// フォントサイズを縮小する
				m_clickedObject->GetComponent<Text>()->fontSize *= 0.9f;
			}
		}
	}	
}

GameObject* EngineObject::SpectatorCamera::GetClickedObject() const
{
	return m_clickedObject;
}

GameObject* EngineObject::SpectatorCamera::GetClickedManipulator() const
{
	return m_clickedManipulator;
}
