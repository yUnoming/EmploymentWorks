// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_NetWorkManager.h"

#include "GameObject.h"
#include "renderer.h"
#include "Transform.h"
#include "Shader.h"
#include "BoxCollider.h"

#include "yUno_GameObjectManager.h"
#include "yUno_SceneManager.h"
#include "yUno_ComponentManager.h"
#include "yUno_CollisionManager.h"
#include "SceneManager.h"

#include <algorithm>

using namespace PublicSystem;


void GameObject::CheckAddComponent(Component* com)
{
	// 当たり判定コンポーネントを追加する？
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
		yUno_SystemManager::yUno_CollisionManager::Push(colCom);	// 格納処理
}

void GameObject::CheckDeleteComponent(Component* com)
{
	// 当たり判定コンポーネントを追加する？
	BoxCollider* colCom = dynamic_cast<BoxCollider*>(com);
	if (colCom != nullptr)
		yUno_SystemManager::yUno_CollisionManager::Erase(colCom);	// 除外処理
}

GameObject::GameObject()
{
	// オブジェクト名の初期化
	ZeroMemory(m_name, sizeof(m_name));
	// Transformコンポーネントを追加
	transform = AddComponent <PublicSystem::Transform> ();
	// Shaderコンポーネントを追加
	AddComponent<PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
}

GameObject::GameObject(yUno_SceneManager* nowScene)
{
	// オブジェクト名の初期化
	ZeroMemory(m_name, sizeof(m_name));
	// Transformコンポーネントを追加
	transform = AddComponent <PublicSystem::Transform>();
	// Shaderコンポーネントを追加
	AddComponent<PublicSystem::Shader>()->Load("Assets\\Shaders\\vertexLightingVS.cso", "Assets\\Shaders\\vertexLightingPS.cso");
	// 現在シーンを代入する
	m_myScene = nowScene;
}

void GameObject::SetName(const char* name)
{
	// オブジェクト名を初期化
	ZeroMemory(m_name, sizeof(m_name));
	
	// オブジェクト名を付ける？
	if (name)
	{
		// オブジェクト名が被っていないか確認し、
		// 実際に付けるオブジェクト名を取得する
		const char* newName = yUno_SystemManager::yUno_GameObjectManager::CheckObjectName(name);
		strcpy_s(m_name, newName);
	}
}

void GameObject::CopyName(const char* name)
{
	// オブジェクト名を初期化
	ZeroMemory(m_name, sizeof(m_name));

	// オブジェクト名を付ける？
	if (name)
		strcpy_s(m_name, name);
}

void GameObject::InitBase()
{
	// オブジェクトの初期化処理
	Init();
}

void GameObject::UnInitBase()
{
	// リスト内のコンポーネント取得
	for (auto com : m_componentList)
	{
		com->UnInit();	// 終了処理
		delete com;		// 削除
	}

	// リストをクリア
	m_componentList.clear();
	m_lateComponentList.clear();

	// オブジェクトの終了処理
	UnInit();
}

bool GameObject::UpdateBase()
{
	int index = 0;	// 要素数

	// 各コンポーネントの更新処理
	for (auto com : m_componentList)
	{
		com->Update();
		
		// スペクテイターカメラ以外？
		if (strcmp(com->gameObject->GetName(), "SpectatorCamera") != 0)
		{
			// オブジェクトがロックされていない？
			if (!yUno_SystemManager::yUno_NetWorkManager::GetServer()->IsRockObject(GetName()))
				// 値が更新されていたらメッセージを送る
				yUno_SystemManager::yUno_ComponentManager::SendMessageBasedOnType(*std::next(m_lateComponentList.begin(), index), com);

			// 現在の値を保存
			yUno_SystemManager::yUno_ComponentManager::SetVariableValue(*std::next(m_lateComponentList.begin(), index), com);
		}
		// カウントを増やす
		index++;
	}
	// オブジェクトの更新処理
	Update();
	
	// オブジェクトを削除する？
	if (isDestroy)
		return true;
	return false;
}

void GameObject::DrawBase()
{
	// リスト内のコンポーネント取得
	for (auto com : m_componentList)
		com->Draw();	// 描画処理

	// オブジェクトの描画処理
	Draw();
}
