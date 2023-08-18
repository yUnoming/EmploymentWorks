// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"
#include "SampleScene.h"
#include "GameObject.h"
#include <SimpleMath.h>


void yUno_SceneManager::InitBase()
{
	// 現在シーンの初期化処理
	Init();
}

void yUno_SceneManager::UnInitBase()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->UnInitBase();	// 終了処理
			delete object;			// 削除
		}
		objectList.clear();	//リストのクリア
	}
	// 現在シーンの終了処理
	m_LoadedScene->UnInit();
}

void yUno_SceneManager::UpdateBase()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->UpdateBase();	// 更新処理
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//ラムダ式
	}

	// 現在シーンの更新処理
	m_LoadedScene->Update();
}


#include "renderer.h"
void yUno_SceneManager::DrawBase()
{
	DirectX::SimpleMath::Matrix matrix = DirectX::SimpleMath::Matrix::Identity;

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->DrawBase(matrix);	// 描画処理
		}
	}

	// 現在シーンの描画処理
	m_LoadedScene->Draw();
}
