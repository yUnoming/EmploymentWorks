// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemNetWorkManager.h"
#include "SpectatorCamera.h"
#include "Transform.h"
#include "Camera.h"

#include "Time.h"
#include "KeyInput.h"
#include "InputPartsName.h"
#include "MouseInput.h"
#include "ScreenInput.h"
#include "Material.h"


void Ctlan::EngineObject::SpectatorCamera::Init()
{
	// コンポーネント追加
	Camera* cam = AddComponent<Camera>();
}

void Ctlan::EngineObject::SpectatorCamera::Update()
{
	// ===== カメラの操作 ===== //
	// オブジェクトを選択していない？（オブジェクトを選択していない場合、カメラの操作が行える）
	if (m_clickedObject == nullptr || m_clickedObject != nullptr && m_clickedObject->GetComponent<PublicSystem::Text>() == nullptr)
	{
		// ----- マウスでカメラ移動 ----- //
		// ホイールボタンが押されている？
		if (MouseInput::GetMouseDown(ScrollWheelButton))
		{
			Vector2 moveAmount = MouseInput::GetCursorMoveAmount();
			Vector3 addVec = Vector3(moveAmount.x, moveAmount.y, 0.0f);
			transform->position += addVec.Rotate(transform->rotation) * 0.01f;
		}
		// ホイールボタンが回転された？
		else if (MouseInput::GetWheelRotation())
		{
			// 前方回転された？
			if (MouseInput::GetWheelRotationForward())
			{
				// 前方に移動
				Vector3 addVec = Vector3(0.0f, 0.0f, 10.0f);
				transform->position += addVec.Rotate(transform->rotation) * 0.01f;
			}
			// 後方回転された
			else
			{
				// 後方に移動
				Vector3 addVec = Vector3(0.0f, 0.0f, -10.0f);
				transform->position += addVec.Rotate(transform->rotation) * 0.01f;
			}
		}
		else
		{
			// ----- キー入力でカメラ移動 ----- //
			// 上矢印キーが押されている？
			if (KeyInput::GetKeyDown(UpArrow))
			{
				Vector3 addVec = Vector3(0.0f, 1.0f, 0.0f);
				transform->position += addVec.Rotate(transform->rotation) * 0.01f;
			}
			// 左矢印キーが押されている？
			if (KeyInput::GetKeyDown(LeftArrow))
			{
				Vector3 addVec = Vector3(-1.0f, 0.0f, 0.0f);
				transform->position += addVec.Rotate(transform->rotation) * 0.01f;
			}
			// 下矢印キーが押されている？
			if (KeyInput::GetKeyDown(DownArrow))
			{
				Vector3 addVec = Vector3(0.0f, -1.0f, 0.0f);
				transform->position += addVec.Rotate(transform->rotation) * 0.01f;
			}
			// 右矢印キーが押されている？
			if (KeyInput::GetKeyDown(RightArrow))
			{
				Vector3 addVec = Vector3(1.0f, 0.0f, 0.0f);
				transform->position += addVec.Rotate(transform->rotation) * 0.01f;
			}
		}

		// ----- カメラ回転 ----- //
		// 右クリックが押されている？
		if (MouseInput::GetMouseDown(RightButton))
		{
			// カーソルの移動量に合わせてカメラを回転
			Vector2 moveAmount = PublicSystem::MouseInput::GetCursorMoveAmount();
			transform->rotation.x -= moveAmount.y * 0.01f * PublicSystem::Time::DeltaTime;
			transform->rotation.y += moveAmount.x * 0.01f * PublicSystem::Time::DeltaTime;
		}
	}

	// ===== クリックしたオブジェクトを取得 ===== //
	static bool isTextMove = false;
	bool isObjectClicked = false;	// オブジェクトがクリックされたかどうか
	// 左クリックされた？
	if (MouseInput::GetMouseDownTrigger(LeftButton))
	{
		// クリックしたオブジェクトを一時的に代入する変数
		GameObject* tmpClickedObject;

		// エディットシーンを参照して、クリックされたオブジェクトを取得
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointGizmo(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		// オブジェクトがクリックされた？
		if (tmpClickedObject)
		{
			m_clickedManipulator = tmpClickedObject;	// クリックされたオブジェクトを代入
			return;										// 更新処理終了
		}

		// 現在のシーンを参照して、クリックされたオブジェクトを取得
		tmpClickedObject = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		// クリックされたオブジェクトがロックされていたら処理を終了
		if (tmpClickedObject && Ctlan::PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->IsRockObject(tmpClickedObject->GetName()))
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
			messageData.message.bodyObject.object.CopyName(m_clickedObject->GetName());
			
			// メッセージを送る処理を実行
			PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->
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
			messageData.message.bodyObject.object.CopyName(m_clickedObject->GetName());

			// メッセージを送る処理を実行
			PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->
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
			messageData.message.bodyObject.object.CopyName(nullptr);

			// メッセージを送る処理を実行
			PrivateSystem::SystemManager::SystemNetWorkManager::GetServer()->
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

Ctlan::PrivateSystem::GameObject* Ctlan::EngineObject::SpectatorCamera::GetClickedObject() const
{
	return m_clickedObject;
}

Ctlan::PrivateSystem::GameObject* Ctlan::EngineObject::SpectatorCamera::GetClickedManipulator() const
{
	return m_clickedManipulator;
}
