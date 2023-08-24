#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <list>
#include <SimpleMath.h>
#include "Component.h"


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		  前方宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
namespace PublicSystem
{
	class Transform;	// PublicSystem::Transformを使うために前方宣言
}


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		 using宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace PublicSystem;


class GameObject
{
	private:
		// ----- variables / 変数 ----- //
		// コンポーネントのリスト
		std::list<Component*> m_Component_List;

		// オブジェクト名
		const char* m_Name = 0;

	protected:
		// ----- variables / 変数 ----- //
		// オブジェクトのアクティブ状態を表す
		// true: 通常動作 false: 機能停止・非表示
		bool m_Active = true;

				// 基本のオブジェクト情報
		Transform* transform = nullptr;

	public:
		// ----- functions / 関数 ----- //
		GameObject();
		virtual ~GameObject() {};

		// オブジェクト単体に関わる処理
		virtual void Init() {};		// 初期化
		virtual void UnInit() {};	// 終了
		virtual void Update() {};	// 更新
		virtual void Draw() {};		// 描画

		// オブジェクト全体に関わる処理
		void InitBase();
		void UnInitBase();
		void UpdateBase();
		void DrawBase(DirectX::SimpleMath::Matrix _parentMatrix);

		//**  コンポーネント操作  **//

		// 　内容：オブジェクトが持っているコンポーネントを取得する
		// 　引数：なし
		// 戻り値：コンポーネントを持っている場合 ===>>   持っているコンポーネントを全て返す
		//		   コンポーネントを持っていない場合 ===>> nullptrを返す
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

		// 　内容：オブジェクトに新たにコンポーネントを追加する
		// 　引数：なし
		// 戻り値：追加したコンポーネント
		template<class T>
		T* AddComponent()
		{
			T* com = new T();
			com->Myself = this;
			if(transform != nullptr)
				com->transform = transform;
			m_Component_List.push_back(com);
			((Component*)com)->Init();
			return com;
		}

		// 　内容：オブジェクトが持っているコンポーネントを削除する
		// 　引数：なし
		// 戻り値：nullptr
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