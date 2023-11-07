#pragma once
/**
* @file		SpectatorCamera.h
* @brief	SpectatorCameraクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"


/// <summary>
///	エンジン内で使うカメラオブジェクト	</summary>
class SpectatorCamera : public GameObject
{
	private:
		// ----- variables / 変数 ----- //
		///<summary>
		///クリックされたオブジェクトを代入する変数	</summary>
		GameObject* m_clickedObject = nullptr;

	public:
		void Init();
		void Update();
};

