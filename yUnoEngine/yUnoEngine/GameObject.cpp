// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"
#include <d3d11.h>


void PublicSystem::GameObject::InitBase()
{
	// オブジェクトの初期化処理
	Init();
}

void PublicSystem::GameObject::UnInitBase()
{
	// リスト内のコンポーネント取得
	for (auto com : m_ComponentList)
	{
		com->UnInit();	// 終了処理
		delete com;		// 削除
	}

	// リストをクリア
	m_ComponentList.clear();

	// オブジェクトの終了処理
	UnInit();
}

void PublicSystem::GameObject::UpdateBase()
{
	// リスト内のコンポーネント取得
	for (auto com : m_ComponentList)
		com->Update();	// 更新処理

	// オブジェクトの更新処理
	Update();
}

void PublicSystem::GameObject::DrawBase(DirectX::SimpleMath::Matrix _parentMatrix)
{
	// マトリックス設定
	DirectX::SimpleMath::Matrix world, trans, rot, scl;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(m_Position.x, m_Position.y, m_Position.z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	scl = DirectX::SimpleMath::Matrix::CreateScale(m_Scale.x, m_Scale.y, m_Scale.z);
	world = trans * rot * scl * _parentMatrix;

	// リスト内のコンポーネント取得
	for (auto com : m_ComponentList)
		com->Draw();	// 描画処理

	// オブジェクトの描画処理
	Draw();
}

// 　内容：オブジェクトが持っているコンポーネントを取得する
// 　引数：なし
// 戻り値：コンポーネントを持っている場合 ===>>   持っているコンポーネントを全て返す
//		   コンポーネントを持っていない場合 ===>> nullptrを返す
template<class T>
T* PublicSystem::GameObject::GetComponent()
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
T* PublicSystem::GameObject::AddComponent()
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
T* PublicSystem::GameObject::DeleteComponent()
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
