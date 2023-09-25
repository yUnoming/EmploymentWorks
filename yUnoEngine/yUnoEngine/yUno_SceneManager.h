#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>
#include <array>
#include "GameObject.h"

namespace yUno_SceneManagement
{
	class yUno_SceneManager
	{
	protected:
		// ----- variables / 変数 ----- //
		// シーン内のオブジェクト
		static std::array<std::list<GameObject*>, 4> m_SceneObject;

		// ロードされたシーン
		yUno_SceneManager* m_LoadedScene;

	public:
		// ----- functions / 関数 ----- //
		yUno_SceneManager() : m_LoadedScene(nullptr) {}// コンストラクタ
		virtual ~yUno_SceneManager() {};	// デストラクタ

		//**  シーン単体に関わる処理  **//
		virtual void Init() {};		// 初期化
		virtual void UnInit() {};	// 終了
		virtual void Update() {};	// 更新
		virtual void Draw() {};		// 描画

		//**  シーン全般に関わる処理  **//
		void InitBase();	// 初期化
		void UnInitBase();	// 終了
		void UpdateBase();	// 更新
		void DrawBase();	// 描画

		//**  シーン関係  **//
		/// <summary>
		/// 選択されたシーンをロード
		/// </summary>
		template<class T> void LoadScene();

		//**  オブジェクト関係  **//
		/// <summary>
		/// オブジェクトを追加
		/// </summary>
		template<class T> T* AddObject(int _layer);

		/// <summary>
		/// オブジェクトを取得
		/// </summary>
		template<class T> T* GetObject();

		/// <summary>
		/// 現在シーンに存在するオブジェクトを全取得
		/// </summary>
		template<class T> std::array<std::list<GameObject*>, 4> GetAllObjects();

	};

	template<class T>
	void yUno_SceneManager::LoadScene()
	{
		// 現在、シーンを開いている？
		if (m_LoadedScene)
		{
			m_LoadedScene->UnInitBase();	// シーンの終了処理
			delete m_LoadedScene;			// シーンの削除
		}

		m_LoadedScene = new T();	// 新たなシーンの生成
		m_LoadedScene->InitBase();	// 新たなシーンの初期化
	}

	template<class T>
	T* yUno_SceneManager::AddObject(int _layer)
	{
		T* obj = new T();						// オブジェクトを生成
		m_SceneObject[_layer].push_back(obj);	// 指定された要素位置に保存
		obj->Init();							// オブジェクトの初期化

		// 生成したオブジェクトを返す
		return obj;
	}
	
	template<class T>
	T* yUno_SceneManager::GetObject()
	{
		for (auto& objectList : m_SceneObject)
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
	
	template<class T>
	inline std::array<std::list<GameObject*>, 4> yUno_SceneManager::GetAllObjects()
	{
		return std::array<std::list<GameObject*>, 4>();
	}
}

using namespace yUno_SceneManagement;
