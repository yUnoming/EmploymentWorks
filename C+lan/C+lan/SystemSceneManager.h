#pragma once
/**
* @file		SystemSceneManager.h
* @brief	SystemSceneManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SceneBase.h"
#include "LaunchSceneInformation.h"

#include <string>
#include <unordered_map>


namespace Ctlan
{
	namespace PrivateSystem
	{
		namespace SystemManager
		{
			/// <summary>
			/// シーンに関する機能をまとめたクラス	</summary>
			class SystemSceneManager
			{
				private:
					// ----- variables / 変数 ----- //
					/// <summary>
					///	エディット用シーン	</summary>
					static SceneBase* m_editScene;
					/// <summary>
					///	起動するシーン情報	</summary>
					static Ctlan::PrivateSystem::Information::LaunchSceneInformation m_launchSceneInfo;
					/// <summary>
					///	セーブするかどうか	</summary>
					static bool isSave;

					// ----- functions / 関数 ----- //
					/// <summary>
					///	現在のシーン状態をセーブ	</summary>
					static void SaveSceneData();
					/// <summary>
					/// シーンのロード	</summary>
					static void LoadScene();

				protected:
					// ----- variables / 変数 ----- //
					/// <summary>
					///	現在ロードされているシーン	</summary>
					static SceneBase* m_loadedScene;
					/// <summary>
					///	シーン一覧	</summary>
					static std::unordered_map<std::string, SceneBase*> m_scenePool;

					// ----- functions / 関数 ----- //
					/// <summary>
					///	シーン情報をロード	</summary>
					/// <param name="loadSceneName">
					///	ロードするシーン名	</param>
					/// <returns>
					/// ロードするシーンがあればシーン情報、無ければnullptr	</returns>
					static SceneBase* LoadSceneData(const char* loadSceneName);

				public:
					// ----- functions / 関数 ----- //
					/// <summary>
					///	コンストラクタ	</summary>
					SystemSceneManager();
					/// <summary>
					///	デストラクタ	</summary>
					virtual ~SystemSceneManager() {};

					//**  シーン全般に関わる処理  **//	
					/// <summary>
					/// 現在シーンの初期化処理	</summary>
					static void InitScene();
					/// <summary>
					///	現在シーンの終了処理	</summary>
					static void UninitScene();
					/// <summary>
					///	現在シーンの更新処理	</summary>
					static void UpdateScene();
					/// <summary>
					///	現在シーンの描画処理	</summary>
					static void DrawScene();

					static void SaveScene() { isSave = true; };

					/// <summary>
					///	新規シーンを作成	</summary>
					/// <param name="sceneName">
					///	新規シーン名	</param>
					static void CreateNewScene(const char* sceneName);
					/// <summary>
					///	エディットシーンを取得	</summary>
					/// <returns>
					///	エディットシーン情報	</returns>
					static SceneBase* GetEditScene() { return m_editScene; };
			};
		}

	}
}
