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
#include <list>
#include <array>
#include "GameObject.h"

/// <summary>
/// シーンに関する機能をまとめたクラス	</summary>
class yUno_SceneManager
{
	protected:
		// ----- variables / 変数 ----- //
		/// <summary>
		/// シーン内のオブジェクト	</summary>
		static std::array<std::list<GameObject*>, 4> m_sceneObject;

		/// <summary>
		///	ロードされたシーン	</summary>
		yUno_SceneManager* m_loadedScene;

	public:
		// ----- functions / 関数 ----- //
		/// <summary>
		///	コンストラクタ	</summary>
		yUno_SceneManager() : m_loadedScene(nullptr) {}
		/// <summary>
		///	デストラクタ	</summary>
		virtual ~yUno_SceneManager() {};

		//**  シーン単体に関わる処理  **//	
		/// <summary>
		///	初期化	</summary>
		virtual void Init() {};
		/// <summary>
		///	終了	</summary>
		virtual void UnInit() {};
		/// <summary>
		///	更新	</summary>
		virtual void Update() {};
		/// <summary>
		///	描画	</summary>
		virtual void Draw() {};

		//**  シーン全般に関わる処理  **//	
		/// <summary>
		/// ベースの初期化処理	</summary>
		void InitBase();
		/// <summary>
		///	ベースの終了処理	</summary>
		void UnInitBase();
		/// <summary>
		///	ベースの更新処理	</summary>
		void UpdateBase();
		/// <summary>
		///	ベースの描画処理	</summary>
		void DrawBase();

		//**  シーン関係  **//
		/// <summary>
		/// 選択したシーンをロード	</summary>
		/// <param name="LoadScene&lt;&gt;();">
		/// &lt;&gt;内にロードするシーンを記述		</param>
		/// <returns>
		/// ロードしたシーン </returns>
		template<class T> T* LoadScene();


		//**  オブジェクト関係  **//
		/// <summary>
		/// シーンにオブジェクトを追加	</summary>
		/// <param name="AddObject&lt;&gt;();">
		/// &lt;&gt;内に追加するオブジェクトを記述		</param>
		/// <param name="layer">
		///	レイヤー番号	</param>
		/// <returns>
		/// 追加したオブジェクト </returns>
		template<class T> T* AddSceneObject(int layer);
		/// <summary>
		/// シーンからオブジェクトを取得	</summary>
		/// <param name="GetObject&lt;&gt;();">
		/// &lt;&gt;内に取得するオブジェクトをを記述		</param>
		/// <returns>
		/// 取得したオブジェクト </returns>
		template<class T> T* GetSceneObject();
		/// <summary>
		/// 現在シーンに存在するオブジェクトを全取得
		/// </summary>
		/// <returns>
		///	全オブジェクトが入ったリスト	</returns>
		template<class T>
		std::array<std::list<GameObject*>, 4> GetAllSceneObjects()
		{
			return m_sceneObject;
		}
};

template<class T> 
T* yUno_SceneManager::LoadScene()
{
	// 現在、シーンを開いている？
	if (m_loadedScene)
	{
		m_loadedScene->UnInitBase();	// シーンの終了処理
		delete m_loadedScene;			// シーンの削除
	}

	m_loadedScene = new T();	// 新たなシーンの生成
	m_loadedScene->InitBase();	// 新たなシーンの初期化

	return (T*)m_loadedScene;
}

template<class T>
T* yUno_SceneManager::AddSceneObject(int layer)
{
	T* obj = new T();						// オブジェクトを生成
	m_sceneObject[layer].push_back(obj);	// 指定された要素位置に保存
	obj->Init();							// オブジェクトの初期化

	// 生成したオブジェクトを返す
	return obj;
}

template<class T>
T* yUno_SceneManager::GetSceneObject()
{
	for (auto& objectList : m_sceneObject)
	{
		for (GameObject* object : objectList)
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
	}

	return nullptr;
}