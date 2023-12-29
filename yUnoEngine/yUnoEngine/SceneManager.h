#pragma once
/**
* @file		SceneManager.h
* @brief	SceneManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"


namespace PublicSystem
{
	/// <summary>
	/// シーンに関する機能をまとめたクラス	</summary>
	class SceneManager : private yUno_SceneManager
	{
		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			/// 現在開いているシーン内のオブジェクトを全て返す	</summary>
			/// <returns>
			/// 現在シーンの全オブジェクト</returns>
			std::array<std::list<GameObject*>, 4> static GetSceneObjectAll();
			
			/// <summary>
			///	現在開いているシーンを取得	</summary>
			/// <returns>
			///	現在シーンのポインター	</returns>
			static SceneBase* GetNowScene();
	};
};

