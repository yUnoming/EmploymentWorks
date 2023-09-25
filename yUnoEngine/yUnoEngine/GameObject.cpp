// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "yUno_SceneManager.h"
#include <algorithm>

using namespace PublicSystem;

GameObject::GameObject()
{
	// Transformコンポーネントを追加
	transform = AddComponent <PublicSystem::Transform> ();
}

GameObject::GameObject(yUno_SceneManager* _nowScene)
{
	// Transformコンポーネントを追加
	transform = AddComponent <PublicSystem::Transform>();
	// 現在シーンを代入する
	m_MyScene = _nowScene;
}

void GameObject::InitBase()
{
	// オブジェクトの初期化処理
	Init();
}

void GameObject::UnInitBase()
{
	// リスト内のコンポーネント取得
	for (auto com : m_Component_List)
	{
		com->UnInit();	// 終了処理
		delete com;		// 削除
	}

	// リストをクリア
	m_Component_List.clear();

	// オブジェクトの終了処理
	UnInit();
}

void GameObject::UpdateBase()
{
	// 各コンポーネントの更新処理
	for (auto com : m_Component_List)
		com->Update();

	// オブジェクトの更新処理
	Update();
}

void GameObject::DrawBase(DirectX::SimpleMath::Matrix _parentMatrix)
{
	// マトリックス設定
	DirectX::SimpleMath::Matrix world, trans, rot, scl;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(transform->Position.x, transform->Position.y, transform->Position.z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(transform->Rotation.y, transform->Rotation.x, transform->Rotation.z);
	scl = DirectX::SimpleMath::Matrix::CreateScale(transform->Scale.x, transform->Scale.y, transform->Scale.z);
	world = rot * trans * scl * _parentMatrix;

	Renderer::SetWorldMatrix(&world);

	// リスト内のコンポーネント取得
	for (auto com : m_Component_List)
		com->Draw();	// 描画処理

	// オブジェクトの描画処理
	Draw();
}
