#pragma once
#include <list>
#include "Component.h"

// 前方参照
class Component;

class GameObject
{
	public :
		// ----- variables ----- //
		// コンポーネントのリスト
		std::list<Component*> m_ComponentList;

		// ----- methods ----- //
		GameObject() {};
		virtual ~GameObject();

		virtual void Init();		// 初期化
		virtual void UnInit();		// 終了
		virtual void Update() {};	// 更新
		virtual void Draw() {};		// 描画

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
