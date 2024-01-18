#pragma once
/**
* @file		yUno_MainManager.h
* @brief	yUno_MainManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>
#include <array>
#include <vector>
#include "BoxCollider.h"


/// <summary>
///	シーンの基礎となるクラス	</summary>
class SceneBase
{
	private:
		// ----- functions / 関数 ----- // 
		/// <summary>
		///	オブジェクト削除処理	</summary>
		/// <param name="object">
		/// 削除するオブジェクト	</param>
		void Delete(GameObject* object);

	protected:
		// ----- variables / 変数 ----- //
		/// <summary>
		///	シーン名	</summary>
		char m_sceneName[30];

		/// <summary>
		/// シーン内のオブジェクト	</summary>
		std::array<std::list<GameObject*>, 4> m_sceneObjectList;

		// Box型の当たり判定用リストを作成
		std::vector<BoxCollider*> m_boxColliderList;

	public:
		// ----- functions / 関数 ----- //
		/// <summary>
		///	コンストラクタ	</summary>
		SceneBase();
		SceneBase(const char* sceneName) { strcpy_s(m_sceneName, sceneName); };

		/// <summary>
		///	デストラクタ	</summary>
		virtual ~SceneBase() {};

		//**  シーン単体に関わる処理  **//	
		/// <summary>
		///	初期化	</summary>
		virtual void Init() {};
		/// <summary>
		///	終了	</summary>
		virtual void UnInit();
		/// <summary>
		///	更新	</summary>
		virtual void Update();
		/// <summary>
		///	描画	</summary>
		virtual void Draw();

		char* GetSceneName() { return m_sceneName; };

		//**  オブジェクト関係  **//
		/// <summary>
		/// シーンに存在するオブジェクトをロード	</summary>
		/// <param name="LoadSceneObject&lt;&gt;();">
		/// &lt;&gt;内にロードするオブジェクトを記述		</param>
		/// <param name="layer">
		///	レイヤー番号	</param>
		/// <param name="name">
		///	ロードするオブジェクトの名称	</param>
		/// <returns>
		/// ロードしたオブジェクト </returns>
		template<class T>
		T* LoadSceneObject(int layer, const char* name)
		{
			T* obj = new T();							// オブジェクトを生成
			obj->CopyName(name);						// オブジェクト名を設定
			m_sceneObjectList[layer].push_back(obj);	// 指定された要素位置に保存
			obj->Init();								// オブジェクトの初期化

			// 生成したオブジェクトを返す
			return obj;
		}
		/// <summary>
		/// シーンにオブジェクトを追加	</summary>
		/// <param name="AddSceneObject&lt;&gt;();">
		/// &lt;&gt;内に追加するオブジェクトを記述		</param>
		/// <param name="layer">
		///	レイヤー番号	</param>
		/// <param name="name">
		///	追加するオブジェクトの名称	</param>
		/// <returns>
		/// 追加したオブジェクト </returns>
		template<class T>
		T* AddSceneObject(int layer, const char* name)
		{
			T* obj = new T(this);						// オブジェクトを生成
			obj->SetName(name);							// オブジェクト名を設定
			m_sceneObjectList[layer].push_back(obj);	// 指定された要素位置に保存
			obj->Init();								// オブジェクトの初期化

			// 生成したオブジェクトを返す
			return obj;
		}
		/// <summary>
		/// シーンからオブジェクトを取得	</summary>
		/// <param name="GetSceneObject&lt;&gt;();">
		/// &lt;&gt;内に取得するオブジェクトをを記述		</param>
		/// <param name="name">
		///	取得するオブジェクトの名称	</param>
		/// <returns>
		/// 取得したオブジェクト、無ければnullptr </returns>
		template<class T> T* GetSceneObject(const char* name)
		{
			// 各スレッド内のオブジェクトリスト取得
			for (auto& objectList : m_sceneObjectList)
			{
				// リスト内のオブジェクト取得
				for (GameObject* object : objectList)
				{
					if (typeid(*object) == typeid(T) && strcmp(object->GetName(), name) == 0)
					{
						return (T*)object;
					}
				}
			}

			return nullptr;
		}
		/// <summary>
		///	シーンからオブジェクトを取得	</summary>
		/// <param name="name">
		/// 取得するオブジェクトの名称	</param>
		/// <returns>
		/// 取得したオブジェクト、無ければnullptr </returns>
		GameObject* GetSceneObject(const char* name)
		{
			// 各スレッド内のオブジェクトリスト取得
			for (auto& objectList : m_sceneObjectList)
			{
				// リスト内のオブジェクト取得
				for (GameObject* object : objectList)
				{
					if (strcmp(object->GetName(), name) == 0)
					{
						return object;
					}
				}
			}

			return nullptr;
		}
		/// <summary>
		///	シーンからオブジェクトを削除	</summary>
		/// <param name="name">
		/// 削除するオブジェクトの名称	</param>
		void DeleteSceneObject(const char* name)
		{
			// 各スレッド内のオブジェクトリスト取得
			for (auto& objectList : m_sceneObjectList)
			{
				// リスト内のオブジェクト取得
				for (GameObject* object : objectList)
				{
					// 名称が一致した？
					if (strcmp(object->GetName(), name) == 0)
					{
						// 削除処理
						Delete(object);
						// オブジェクトリストから除外
						objectList.erase(std::find(objectList.begin(), objectList.end(), object));
						// オブジェクトを削除
						delete object;
						return;
					}
				}
			}
		}
		/// <summary>
		///	シーンからオブジェクトを削除	</summary>
		/// <param name="name">
		/// 削除するオブジェクト情報	</param>
		void DeleteSceneObject(GameObject* deleteObj)
		{
			// 各スレッド内のオブジェクトリスト取得
			for (auto& objectList : m_sceneObjectList)
			{
				// リスト内のオブジェクト取得
				for (GameObject* object : objectList)
				{
					// オブジェクトが一致した？
					if (object == deleteObj)
					{
						// 削除処理
						Delete(object);
						// オブジェクトリストから除外
						objectList.erase(std::find(objectList.begin(), objectList.end(), object));
						return;
					}
				}
			}
		}


		/// <summary>
		/// 現在シーンに存在するオブジェクトを全取得	</summary>
		/// <returns>
		///	全オブジェクトが入ったリスト	</returns>
		std::array<std::list<GameObject*>, 4> GetAllSceneObjects()
		{
			return m_sceneObjectList;
		}
};

