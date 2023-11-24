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
		transform->Position.y += 0.01f;
	if (KeyInput::GetKeyDown(LeftArrow))
		transform->Position.x -= 0.01f;
	if (KeyInput::GetKeyDown(DownArrow))
		transform->Position.y -= 0.01f;
	if (KeyInput::GetKeyDown(RightArrow))
		transform->Position.x += 0.01f;

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
			// クリックされていたオブジェクトのマテリアルを変更
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			
			// クリックされたオブジェクトをメンバ変数に代入
			m_clickedObject = tmpClickedObject;
			// クリックされたオブジェクトのマテリアルを変更
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 0.0f, 0.0f, 1.0f));

			// 送るメッセージを代入する配列
			char sendMessage[256];
			ZeroMemory(sendMessage, sizeof(sendMessage));

			// 送りたい情報を文字列に置換
			sprintf_s(sendMessage, "%d %s",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject,	// 送信するメッセージのタイプ
				m_clickedObject->GetName());											// オブジェクト名
				// メッセージを送る処理を実行
				yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// オブジェクトがクリックされた？
		else if (tmpClickedObject)
		{
			// クリックされたオブジェクトをメンバ変数に代入
			m_clickedObject = tmpClickedObject;
			// クリックされたオブジェクトのマテリアルを変更
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 0.0f, 0.0f, 1.0f));

			// 送るメッセージを代入する配列
			char sendMessage[256];
			ZeroMemory(sendMessage, sizeof(sendMessage));

			// 送りたい情報を文字列に置換
			sprintf_s(sendMessage, "%d %s",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject,	// 送信するメッセージのタイプ
				m_clickedObject->GetName());											// オブジェクト名
			// メッセージを送る処理を実行
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
		// オブジェクトが解除された？
		else if (!tmpClickedObject && m_clickedObject)
		{
			// クリックされていたオブジェクトのマテリアルを変更
			m_clickedObject->GetComponent<Material>()->SetMaterialColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			// クリックオブジェクトを解除
			m_clickedObject = nullptr;

			// 送るメッセージを代入する配列
			char sendMessage[256];
			ZeroMemory(sendMessage, sizeof(sendMessage));

			// 送りたい情報を文字列に置換
			sprintf_s(sendMessage, "%d %s",
				yUno_SystemManager::yUno_NetWorkManager::MessageType::ClickedObject,	// 送信するメッセージのタイプ
				nullptr);																// オブジェクト名
			// メッセージを送る処理を実行
			yUno_SystemManager::yUno_NetWorkManager::GetServer()->SendData(sendMessage);
		}
	}

	// ===== クリックしたオブジェクトの操作 ===== //
	// オブジェクトを取得している？
	if (m_clickedObject)
	{
		if (KeyInput::GetKeyDown(W))
			m_clickedObject->transform->Position.z += 0.01f;
		if (KeyInput::GetKeyDown(A))
			m_clickedObject->transform->Position.x -= 0.01f;
		if (KeyInput::GetKeyDown(S))
			m_clickedObject->transform->Position.z -= 0.01f;
		if (KeyInput::GetKeyDown(D))
			m_clickedObject->transform->Position.x += 0.01f;
	}	
}
