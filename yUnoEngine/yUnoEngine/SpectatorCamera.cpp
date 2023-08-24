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


void SpectatorCamera::Init()
{
	AddComponent<Camera>();
}

void SpectatorCamera::Update()
{
	if (KeyInput::GetKeyDown(W))
		transform->Position.y += 0.01f;
	if (KeyInput::GetKeyDown(A))
		transform->Position.x -= 0.01f;
	if (KeyInput::GetKeyDown(S))
		transform->Position.y -= 0.01f;
	if (KeyInput::GetKeyDown(D))
		transform->Position.x += 0.01f;

	if (MouseInput::GetMouseDown_Trigger(LeftButton))
	{
		Vector2 ClickedPosition = ScreenInput::GetScreenPosition(MouseInput::GetCursorPosition());
	}
}
