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


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		  using宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace PublicSystem;


void SpectatorCamera::Update()
{
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
		// クリックした位置にオブジェクトがある場合、そのオブジェクトを取得する
		Clicked_Object = GetComponent<Camera>()->GetScreenPointObject(ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition()));
		if (Clicked_Object)
			Clicked_Object->transform->Position.y += 0.1f;
	}
}
