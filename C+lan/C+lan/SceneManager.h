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
#include "SystemSceneManager.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// シーンに関する機能をまとめたクラス	</summary>
		class SceneManager : private PrivateSystem::SystemManager::SystemSceneManager
		{
			public:
				// ----- functions / 関数 ----- //
				/// <summary>
				/// 現在開いているシーン内のオブジェクトを全て返す	</summary>
				/// <returns>
				/// 現在シーンの全オブジェクト</returns>
				std::array<std::list<PrivateSystem::GameObject*>, 4> static GetSceneObjectAll();

				/// <summary>
				///	現在開いているシーンを取得	</summary>
				/// <returns>
				///	現在シーンのポインター	</returns>
				static SceneBase* GetNowScene();

				/// <summary>
				///	シーンをロードする	</summary>
				/// <param name="sceneName">
				///	ロードするシーン名	</param>
				static void LoadScene(const char* sceneName);
		};
	};
}