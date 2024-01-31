// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "SystemNetWorkManager.h"

#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "Shader.h"
#include "BoxCollider.h"

#include "SceneBase.h"
#include "EditScene.h"

#include "SystemGameObjectManager.h"
#include "SystemSceneManager.h"
#include "SystemComponentManager.h"
#include "SystemCollisionManager.h"
#include "SceneManager.h"

#include <algorithm>


void Ctlan::PrivateSystem::GameObject::CheckAddComponent(Component* com)
{
	// 当たり判定コンポーネントを追加する？
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
	{
		Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Push(colCom);	// 格納処理
	}
}

void Ctlan::PrivateSystem::GameObject::CheckDeleteComponent(Component* com)
{
	// 当たり判定コンポーネントを追加する？
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
	{
		Ctlan::PrivateSystem::SystemManager::SystemCollisionManager::Erase(colCom);	// 除外処理
	}
}

Ctlan::PrivateSystem::GameObject::GameObject()
{
	// オブジェクト名の初期化
	ZeroMemory(m_name, sizeof(m_name));
	// Transformコンポーネントを追加
	transform = AddComponent <Ctlan::PublicSystem::Transform> ();
	// Shaderコンポーネントを追加
	AddComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
}

Ctlan::PrivateSystem::GameObject::GameObject(SceneBase* nowScene)
{
	// オブジェクト名の初期化
	ZeroMemory(m_name, sizeof(m_name));
	// Transformコンポーネントを追加
	transform = AddComponent <Ctlan::PublicSystem::Transform>();
	// Shaderコンポーネントを追加
	AddComponent<Ctlan::PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
	// 現在シーンを代入する
	m_myScene = nowScene;
}

void Ctlan::PrivateSystem::GameObject::SetName(const char* name)
{
	// オブジェクト名を初期化
	ZeroMemory(m_name, sizeof(m_name));
	
	// オブジェクト名を付ける？
	if (name)
	{
		// オブジェクト名が被っていないか確認し、
		// 実際に付けるオブジェクト名を取得する
		const char* newName = SystemManager::SystemGameObjectManager::CheckObjectName(name);
		strcpy_s(m_name, newName);
	}
}

void Ctlan::PrivateSystem::GameObject::CopyName(const char* name)
{
	// オブジェクト名を初期化
	ZeroMemory(m_name, sizeof(m_name));

	// オブジェクト名を付ける？
	if (name)
		strcpy_s(m_name, name);
}

void Ctlan::PrivateSystem::GameObject::InitBase()
{
	int index = 0;	// 要素数

	// 各コンポーネントの初期値保存
	for (auto com : m_componentList)
	{
		// 現在の値を保存
		SystemManager::SystemComponentManager::SetVariableValue(*std::next(m_lateComponentList.begin(), index), com);
		index++;
	}

	// オブジェクトの初期化処理
	Init();
}

void Ctlan::PrivateSystem::GameObject::UninitBase()
{
	// リスト内のコンポーネント取得
	for (auto com : m_componentList)
	{
		com->Uninit();	// 終了処理
		delete com;		// 削除
	}

	// リストをクリア
	m_componentList.clear();
	m_lateComponentList.clear();

	// オブジェクト情報を削除
	SystemManager::SystemGameObjectManager::DeleteObjectNameData(m_name);
	// オブジェクトの終了処理
	Uninit();
}

bool Ctlan::PrivateSystem::GameObject::UpdateBase()
{
	int index = 0;	// 要素数

	// 各コンポーネントの更新処理
	for (auto com : m_componentList)
	{
// デバッグ時の処理
#if _DEBUG
		// デモプレイ中？
		Ctlan::EngineScene::EditScene* editScene = (EngineScene::EditScene*)SystemManager::SystemSceneManager::GetEditScene();
		if (editScene->IsDemoPlay())
		{
			com->Update();	// 更新処理
		}
		// デモプレイ中ではない
		else
		{
			// テキストコンポーネント？
			if (dynamic_cast<Text*>(com) != nullptr)
				com->Update();	// 更新処理
			// エディット用のオブジェクト？
			else if (editScene == m_myScene)
				com->Update();	// 更新処理

			// エディット用のオブジェクトではない？
			if (editScene != m_myScene)
			{
				// オブジェクトがロックされていない？
				if (!SystemManager::SystemNetWorkManager::GetServer()->IsRockObject(GetName()))
					// 値が更新されていたらメッセージを送る
					SystemManager::SystemComponentManager::SendMessageBasedOnType(*std::next(m_lateComponentList.begin(), index), com);

				// 現在の値を保存
				SystemManager::SystemComponentManager::SetVariableValue(*std::next(m_lateComponentList.begin(), index), com);
			}
			index++;		// カウントを増やす
		}
#else
		// 通常処理		
		com->Update();	// 更新処理
#endif
	}
// デバッグ時の処理
#if _DEBUG
	// デモプレイ中？
	EngineScene::EditScene* editScene = (EngineScene::EditScene*)SystemManager::SystemSceneManager::GetEditScene();
	if (editScene->IsDemoPlay())
		Update();	// オブジェクトの更新処理
	// エディット用のオブジェクト？
	else if (editScene == m_myScene)
		Update();	// オブジェクトの更新処理
// デバッグ時以外
#else
	// オブジェクトの更新処理
	Update();
#endif
// 通常処理
	// オブジェクトを削除する？
	if (isDestroy)
		return true;
	return false;
}

void Ctlan::PrivateSystem::GameObject::DrawBase()
{
	// リスト内のコンポーネント取得
	for (auto com : m_componentList)
		com->Draw();	// 描画処理

	// オブジェクトの描画処理
	Draw();
}
