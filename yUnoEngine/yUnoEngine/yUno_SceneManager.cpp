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

	// ビュー変換後列作成
	DirectX::SimpleMath::Matrix m_ViewMatrix;

	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
	//	m_ViewMatrix = m_ViewMatrix.CreateLookAt(m_Position, m_Target, up);					

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクション行列の生成
	constexpr float fieldOfView = DirectX::XMConvertToRadians(45.0f);    // 視野角

	float aspectRatio = static_cast<float>(960) / static_cast<float>(540);	// アスペクト比	
	float nearPlane = 1.0f;       // ニアクリップ
	float farPlane = 1000.0f;      // ファークリップ

	//プロジェクション行列の生成
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, aspectRatio, nearPlane, farPlane);	// 左手系にした　20230511 by suzuki.tomoki

	// DIRECTXTKのメソッドは右手系　20230511 by suzuki.tomoki
	// 右手系にすると３角形頂点が反時計回りになるので描画されなくなるので注意
	// このコードは確認テストのために残す
//	projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlane, farPlane);

	Renderer::SetProjectionMatrix(&projectionMatrix);

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
