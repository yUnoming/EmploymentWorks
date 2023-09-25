#pragma once
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
namespace PublicSystem
{
	class Transform;	// PublicSystem::Transformを使うための前方宣言
}

namespace yUno_SceneManagement
{
	class yUno_SceneManager;	// yUno_SceneManagement::yUno_SceneManagerを使うための前方宣言
}


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 using宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace PublicSystem;
using namespace yUno_SceneManagement;


class GameObject
{
	private:
		// ----- variables / 変数 ----- //
		// コンポーネントのリスト
		std::list<Component*> m_Component_List;

		// オブジェクト名
		const char* m_Name = 0;

		// 自身がいるシーンの情報
		yUno_SceneManager* m_MyScene = nullptr;


		// ----- functions / 関数 ----- //

	protected:
		// ----- variables / 変数 ----- //
		// オブジェクトのアクティブ状態を表す
		// true: 通常動作 false: 機能停止・非表示
		bool m_Active = true;

	public:
		// ----- variables / 変数 ----- //
		// 基本のオブジェクト情報
		Transform* transform = nullptr;

		// ----- functions / 関数 ----- //
		GameObject();
		GameObject(yUno_SceneManager* _nowScene);
		virtual ~GameObject() {};

		// オブジェクト単体に関わる処理
		virtual void Init() {};			// 初期化
		virtual void UnInit() {};		// 終了
		virtual void Update() {};		// 更新
		virtual void Draw() {};			// 描画
		
		// 当たり判定が当たった場合
		virtual void HitCollision()
		{
			for (auto com : m_Component_List)
			{
				com->HitCollision();
			}
		};

		// オブジェクト全体に関わる処理
		void InitBase();
		void UnInitBase();
		void UpdateBase();
		void DrawBase(DirectX::SimpleMath::Matrix _parentMatrix);

		//**  コンポーネント操作  **//
		/// <summary>
		// 　内容：オブジェクトが持っているコンポーネントを取得する
		// 　引数：なし
		// 戻り値：コンポーネントを持っている場合 ===>>   持っているコンポーネントを返す
		//		   コンポーネントを持っていない場合 ===>> nullptrを返す
		/// </summary>
		template<class T>
		T* GetComponent()
		{
			for (auto com : m_Component_List)
			{
				T* Component = dynamic_cast<T*>(com);
				if (Component != nullptr)
					return Component;
			}
			return nullptr;
		}

		/// <summary>
		// 　内容：オブジェクトに新たにコンポーネントを追加する
		// 　引数：なし
		// 戻り値：追加したコンポーネント
		/// </summary>
		template<class T>
		T* AddComponent()
		{
			T* com = new T();	

			// コンポーネントに自身が追加されるオブジェクトを代入
			com->Myself = this;

			if(transform != nullptr)			// Transformコンポーネントが自身に追加されている？
				com->transform = transform;		// 追加するコンポーネントにTransform情報を代入

			m_Component_List.push_back(com);	// コンポーネントリストに追加
			//Set_FitComponentList<T>(com);		// 適したリストに入れる関数を実行

			((Component*)com)->Init();
			return com;
		}

		/// <summary>
		// 　内容：オブジェクトが持っているコンポーネントを削除する
		// 　引数：なし
		// 戻り値：nullptr
		/// </summary>
		template<class T>
		void DeleteComponent()
		{
			for (auto com : m_Component_List)
			{
				T* Component = dynamic_cast<T*>(com);
				if (Component != nullptr)
				{
					Component->UnInit();
					delete Component;
				}
			}
		}
};