// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"
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
	for (auto& objectList : m_SceneObject)
	{
		// リスト内のオブジェクト取得
		for (PublicSystem::GameObject* object : objectList)
		{
			object->UnInit();	// 終了処理
			delete object;		// 削除
		}
		objectList.clear();		//リストのクリア
	}
	// 現在シーンの終了処理
	UnInit();
}

void yUno_SceneManager::UpdateBase()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_SceneObject)
	{
		// リスト内のオブジェクト取得
		for (PublicSystem::GameObject* object : objectList)
		{
			object->Update();	// 更新処理
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//ラムダ式
	}

	// 現在シーンの更新処理
	Update();
}

void yUno_SceneManager::DrawBase()
{
	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_SceneObject)
	{
		// リスト内のオブジェクト取得
		for (PublicSystem::GameObject* object : objectList)
		{
			object->Draw();	// 描画処理
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//ラムダ式
	}

	// 現在シーンの描画処理
	Draw();
}
