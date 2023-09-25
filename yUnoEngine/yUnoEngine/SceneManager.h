#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"


namespace PublicSystem
{
	/// <summary>
	/// シーンに関する操作を行えるクラス
	/// </summary>
	class SceneManager : private yUno_SceneManager
	{
		public:

			// ----- functions / 関数 ----- //
			/// <summary>
			/// 現在開いているシーン内のオブジェクトを全て返す
			/// </summary>
			/// <returns>現在シーンの全オブジェクト</returns>
			std::array<std::list<GameObject*>, 4> static GetSceneObjectAll();
	};
};

