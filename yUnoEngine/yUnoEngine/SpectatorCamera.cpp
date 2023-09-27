// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
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
	if (MouseInput::GetMouseDown_Trigger(LeftButton))
	{
		// クリックしたオブジェクトを一時的に代入する変数
		GameObject* Tmp_Clicked_Object;

		// クリックした位置にオブジェクトがある場合、そのオブジェクトを取得
		// 取得された状態でオブジェクトがない場所がクリックされたら、取得を解除する
		Tmp_Clicked_Object = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		
		// 別のオブジェクトがクリックされた？
		if (m_Clicked_Object && Tmp_Clicked_Object != m_Clicked_Object)
		{
			// クリックされていたオブジェクトのマテリアルを変更
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			
			// クリックされたオブジェクトをメンバ変数に代入
			m_Clicked_Object = Tmp_Clicked_Object;
			// クリックされたオブジェクトのマテリアルを変更
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		}
		// オブジェクトがクリックされた？
		else if (Tmp_Clicked_Object)
		{
			// クリックされたオブジェクトをメンバ変数に代入
			m_Clicked_Object = Tmp_Clicked_Object;
			// クリックされたオブジェクトのマテリアルを変更
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		}
		// オブジェクトが解除された？
		else if (!Tmp_Clicked_Object && m_Clicked_Object)
		{
			// クリックされていたオブジェクトのマテリアルを変更
			m_Clicked_Object->GetComponent<Material>()->SetMateiralColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}


	// ===== クリックしたオブジェクトの操作 ===== //
	// オブジェクトを取得している？
	if (m_Clicked_Object)
	{
		if (KeyInput::GetKeyDown(W))
			m_Clicked_Object->transform->Position.z += 0.01f;
		if (KeyInput::GetKeyDown(A))
			m_Clicked_Object->transform->Position.x -= 0.01f;
		if (KeyInput::GetKeyDown(S))
			m_Clicked_Object->transform->Position.z -= 0.01f;
		if (KeyInput::GetKeyDown(D))
			m_Clicked_Object->transform->Position.x += 0.01f;

	}
		
}
