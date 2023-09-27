#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
//										//
// 　　エンジン内で使用されるカメラ　　 //
//										//
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
class SpectatorCamera : public GameObject
{
	private:
		// ----- variables / 変数 ----- //
		///<summary>
		///クリックされたオブジェクトを代入する変数	</summary>
		GameObject* m_Clicked_Object = nullptr;

	public:
		void Init();
		void Update();
};

