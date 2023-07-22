#pragma once
#include <list>

// 前方参照
class GameObject;

class Component
{
	public:
		// ＊＊＊＊＊ variable ＊＊＊＊＊ //
		// オブジェクトのリスト定義
		std::list<GameObject*> m_GameObjectList;
		// 自身
		GameObject* Parent = nullptr;

		// ＊＊＊＊＊ function ＊＊＊＊＊ //
		// コンストラクタ
		Component() {};
		// デストラクタ
		virtual ~Component() {};

		// 初期化
		virtual void Init() {};
		// 終了
		virtual void UnInit() {};
		// 更新
		virtual void Update() {};
		// 描画
		virtual void Draw() {};
};

