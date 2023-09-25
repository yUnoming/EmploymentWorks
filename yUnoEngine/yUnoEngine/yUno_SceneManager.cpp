// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_SceneManager.h"
#include "SampleScene.h"
#include "GameObject.h"
#include "BoxCollider.h"
#include <SimpleMath.h>

std::array<std::list<GameObject*>, 4> yUno_SceneManager::m_SceneObject;


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
	// Box型の当たり判定用リストを作成
	std::list<BoxCollider*> BoxCollider_List;

	// 各スレッド内のオブジェクトリスト取得
	for (auto& objectList : m_LoadedScene->m_SceneObject)
	{
		// リスト内のオブジェクト取得
		for (GameObject* object : objectList)
		{
			object->UpdateBase();	// 更新処理
			
			// "BoxCollider"コンポーネントを取得
			BoxCollider *boxcol = object->GetComponent<BoxCollider>();
			// 取得出来た？
			if (boxcol != nullptr)
				BoxCollider_List.push_back(boxcol);	// リストに格納しておく
		}

		//objectList.remove_if([](GameObject* object) {return object->Destroy(); });	//ラムダ式
	}

	// 相手側の当たり判定用リストを作成
	std::list<BoxCollider*> Other_BoxCollider_List = BoxCollider_List;
	Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());

	// ===== "BoxCollider"同士の当たり判定 ===== //
	for (auto my_BoxCol : BoxCollider_List)
	{
		// 当たり判定を全通り行った？
		if (Other_BoxCollider_List.empty())
			break;	// 判定終了

		for (auto other_BoxCol : Other_BoxCollider_List)
		{
			my_BoxCol->CalcCollision(other_BoxCol);	// 計算処理
		}

		// 当たり判定の相手用リストの０番目（始めに格納されている情報）を削除する
		// ※当たり判定を重複して判定することを阻止するため
		Other_BoxCollider_List.erase(Other_BoxCollider_List.cbegin());
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
