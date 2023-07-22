#pragma once
#include <list>
#include "Component.h"

// 前方参照
class Component;

class GameObject
{
	public :
		// ＊＊＊＊＊ variable ＊＊＊＊＊ //
		// コンポーネントのリスト
		std::list<Component*> m_ComponentList;

		// ＊＊＊＊＊ function ＊＊＊＊＊ //
		// コンストラクタ
		GameObject() {};
		// デストラクタ
		virtual ~GameObject();

		// 更新
		void Update();
		// 描画
		void Draw();

		// コンポーネント取得
		template<class T>
		T* GetComponent();
		// コンポーネント追加
		template<class T>
		T* AddComponent();
		// コンポーネント削除
		template<class T>
		T* DeleteComponent();
};
