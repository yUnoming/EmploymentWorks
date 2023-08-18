// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SpectatorCamera.h"
#include "Transform.h"
#include "Camera.h"

#include "KeyInput.h"
#include "KeyName.h"


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
	if (KeyInput::GetKeyDown(S))
		transform->Position.y -= 0.001f;
	if (KeyInput::GetKeyDown(W))
		transform->Position.y += 0.001f;
}
