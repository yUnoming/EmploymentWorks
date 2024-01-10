#pragma once
/**
* @file		yUno_SceneManager.h
* @brief	yUno_SceneManagerクラスのヘッダーファイル
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


/// <summary>
/// シーンに関する機能をまとめたクラス	</summary>
class yUno_SceneManager
{
	private :
		// ----- variables / 変数 ----- //
		/// <summary>
		///	エディット用シーン	</summary>
		static SceneBase* m_editScene;
		/// <summary>
		///	起動するシーン情報	</summary>
		static yUnoEngine::Information::LaunchSceneInformation m_launchSceneInfo;

		// ----- functions / 関数 ----- //
		/// <summary>
		///	現在のシーン状態をセーブ	</summary>
		static void SaveSceneData();
		/// <summary>
		/// 選択したシーンをロード	</summary>
		/// <param name="LoadScene&lt;&gt;();">
		/// &lt;&gt;内にロードするシーンを記述		</param>
		/// <returns>
		/// ロードしたシーン </returns>
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
		yUno_SceneManager();
		/// <summary>
		///	デストラクタ	</summary>
		virtual ~yUno_SceneManager() {};

		//**  シーン全般に関わる処理  **//	
		/// <summary>
		/// 現在シーンの初期化処理	</summary>
		static void InitScene();
		/// <summary>
		///	現在シーンの終了処理	</summary>
		static void UnInitScene();
		/// <summary>
		///	現在シーンの更新処理	</summary>
		static void UpdateScene();
		/// <summary>
		///	現在シーンの描画処理	</summary>
		static void DrawScene();

		/// <summary>
		///	新規シーンを作成	</summary>
		/// <param name="sceneName">
		///	新規シーン名	</param>
		static void CreateNewScene(const char* sceneName);
#if _DEBUG
		static SceneBase* GetEditScene() { return m_editScene; };
#endif
};
