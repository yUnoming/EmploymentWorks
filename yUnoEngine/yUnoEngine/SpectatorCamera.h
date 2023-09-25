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
		///クリックされたオブジェクトを代入する変数	///</summary>
		const GameObject* Clicked_Object;

	public:
		void Update();
};

