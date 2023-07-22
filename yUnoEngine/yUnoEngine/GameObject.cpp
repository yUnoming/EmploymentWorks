#include "GameObject.h"

// 　内容：GameObjectクラスのデストラクタ
// 　引数：なし
// 戻り値：なし
GameObject::~GameObject()
{
	// コンポーネントの数だけループ
	for (auto com : m_ComponentList)
		delete com;
}

// 　内容：オブジェクトが持っている各種コンポーネントを更新処理を実行する
// 　引数：なし
// 戻り値：なし
void GameObject::Update()
{
	for (auto com : m_ComponentList)
		com->Update();
}

// 　内容：オブジェクトが持っている各種コンポーネントの描画処理を実行する
// 　引数：なし
// 戻り値：なし
void GameObject::Draw()
{
	for (auto com : m_ComponentList)
		com->Draw();
}

// 　内容：オブジェクトが持っているコンポーネントを取得する
// 　引数：なし
// 戻り値：コンポーネントを持っている場合 ===>>   持っているコンポーネントを全て返す
//		   コンポーネントを持っていない場合 ===>> nullptrを返す
template<class T>
T* GameObject::GetComponent()
{
	for (auto com : m_ComponentList)
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
T* GameObject::AddComponent()
{
	T* Component = new T();
	m_ComponentList.push_back(Component);
	Component->Init();
	return Component;
}

// 　内容：オブジェクトが持っているコンポーネントを削除する
// 　引数：なし
// 戻り値：nullptr
template<class T>
T* GameObject::DeleteComponent()
{
	for (auto com : m_ComponentList)
	{
		T* Component = dynamic_cast<T*>(com);
		if (Component != nullptr)
		{
			Component->UnInit();
			delete Component;
			return nullptr;
		}
	}
	return nullptr;
}
