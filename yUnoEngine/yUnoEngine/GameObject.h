#pragma once
/**
* @file		GameObject.h
* @brief	GameObjectクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>
#include <SimpleMath.h>
#include <iostream>
#include "Component.h"

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		  前方宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
/// <summary>
/// ユーザーが使えるシステム </summary>
namespace PublicSystem
{
	class Transform;	// PublicSystem::Transformを使うための前方宣言
}

class yUno_SceneManager;	// yUno_SceneManagerを使うための前方宣言


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 using宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace PublicSystem;

/// <summary>
/// オブジェクトに持たせたい要素をまとめたクラス	</summary>
class GameObject
{
	private:
		// ----- variables / 変数 ----- //
		/// <summary>
		/// 保持しているコンポーネントを格納するリスト		</summary>
		std::list<Component*> m_componentList;

		/// <summary>
		/// オブジェクト名	</summary>
		const char* m_name = 0;

		/// <summary>
		/// 自身がいるシーンの情報		</summary>
		yUno_SceneManager* m_myScene = nullptr;

	protected:
		// ----- variables / 変数 ----- //
		/// <summary>
		/// オブジェクトのアクティブ状態
		/// （true: アクティブ false: 非アクティブ）</summary>
		bool m_active = true;

	public:
		// ----- variables / 変数 ----- //
		/// <summary>
		/// トランスフォーム	</summary>
		Transform* transform = nullptr;

		// ----- functions / 関数 ----- //
		/// <summary>
		/// コンストラクタ		</summary>
		GameObject();
		/// <summary>
		///	引数付きコンストラクタ	</summary>
		/// <param name="_nowScene">
		///	現在のシーン	</param>
		GameObject(yUno_SceneManager* nowScene);
		/// <summary>
		/// デストラクタ	</summary>
		virtual ~GameObject() {};

		// オブジェクト単体に関わる処理
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
		/// <summary>
		/// 当たり判定時	</summary>
		virtual void HitCollision()
		{
			// リスト内のコンポーネントを一つずつ取得
			for (auto com : m_componentList)
			{
				com->HitCollision();
			}
		};

		// オブジェクト全体に関わる処理
		/// <summary>
		/// ベースの初期化処理	</summary>
		void InitBase();
		/// <summary>
		/// ベースの終了処理	</summary>
		void UnInitBase();
		/// <summary>
		/// ベースの更新処理	</summary>
		/// </summary>
		void UpdateBase();
		/// <summary>
		/// ベースの描画処理	</summary>
		/// <param name="parentMatrix">
		///	親の座標行列（親がいない場合は正規化された座標行列）	</param>
		void DrawBase(DirectX::SimpleMath::Matrix parentMatrix);

		//**  コンポーネント操作  **//
		/// <summary>
		/// コンポーネントを取得 </summary>
		/// <param name="GetComponent&lt;&gt;();">
		/// &lt;&gt;内に取得したいコンポーネントを記述		</param>
		/// <returns>
		/// 取得したコンポーネント </returns>
		template<class T>
		T* GetComponent()
		{
			// リスト内のコンポーネントを一つずつ取得
			for (auto com : m_componentList)
			{
				T* component = dynamic_cast<T*>(com);
				
				// 取得したいコンポーネントと合致した？
				if (component != nullptr)
					return component;
			}
			return nullptr;
		}
		/// <summary>
		/// コンポーネントを追加
		/// </summary>
		/// <param name="AddComponent&lt;&gt;();">
		/// &lt;&gt;内に追加したいコンポーネントを記述		</param>
		/// <returns>
		/// 追加したコンポーネント		</returns>
		template<class T>
		T* AddComponent()
		{
			T* com = new T();	

			// コンポーネントに自身が追加されるオブジェクトを代入
			com->Myself = this;

			// Transformコンポーネントが自身に追加されている？
			if(transform != nullptr)
				com->transform = transform;		// 追加するコンポーネントにTransform情報を代入

			m_componentList.push_back(com);	// コンポーネントリストに追加

			((Component*)com)->Init();			// コンポーネントの初期化処理
			return com;
		}
		/// <summary>
		/// コンポーネントを削除
		/// </summary>
		/// <param name="DeleteComponent&lt;&gt;();">
		/// &lt;&gt;内に削除したいコンポーネントを記述		</param>
		template<class T>
		void DeleteComponent()
		{
			// リスト内のコンポーネントを一つずつ取得
			for (auto com : m_componentList)
			{
				T* Component = dynamic_cast<T*>(com);
				
				// 取得したいコンポーネントと合致した？
				if (Component != nullptr)
				{
					Component->UnInit();		// コンポーネントの終了処理
					delete Component;
				}
			}
		}
};