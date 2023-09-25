// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Camera.h"
#include "renderer.h"
#include "Transform.h"
#include <math.h>
#include <SimpleMath.h>
#include <algorithm>
#include "SceneManager.h"
#include "CalculationHit.h"

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　		  using宣言		 　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
using namespace PublicSystem;


void PublicSystem::Camera::Draw()
{
	AddComponent<Transform>();
	// ビュー変換行列作成
	DirectX::SimpleMath::Matrix ViewMatrix;

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 target = DirectX::XMFLOAT3(transform->Position.x, transform->Position.y, transform->Position.z + 10.0f);
	DirectX::XMFLOAT3 up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	position.x = transform->Position.x;
	position.y = transform->Position.y;
	position.z = transform->Position.z;

	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);

	ViewMatrix = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);

	Renderer::SetViewMatrix(&ViewMatrix);
	
	//プロジェクション行列の生成
	float Fov = FieldOfView * 3.14159265f / 180.0f;
	float aspectRatio = static_cast<float>(960) / static_cast<float>(540);	// アスペクト比	

	//プロジェクション行列の生成
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(Fov, aspectRatio, NearClip, FarClip);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

GameObject* PublicSystem::Camera::GetScreenPointObject(Vector2 _screenPoint)
{
	// ===== 引数で受け取ったスクリーン座標をワールド座標に変換する処理 ===== //
	// カメラの最遠描画地点の幅を求める
	Vector2 ViewScreen_Wide = Vector2
		(
			FarClip * tanf(FieldOfView / 2 * 3.14159265f / 180.0f) * (960.0f / 540.0f),	// 横幅
			FarClip * tanf(FieldOfView / 2 * 3.14159265f / 180.0f)						// 縦幅
		);

	// クライアント領域を取得
	RECT rect;
	GetClientRect(Application::Get_Window(), &rect);

	// スクリーンの中心座標を計算
	Vector2 Screen_CenterPosition = Vector2(rect.right / 2, rect.bottom / 2);
	Vector2 Center_To_Point_Length = _screenPoint - Screen_CenterPosition;
	Vector2 LengthRate = Center_To_Point_Length / Screen_CenterPosition;

	// 引数の値をカメラの最遠描画地点の座標位置に割り当てる
	Vector3 WorldPoint_Position = Vector3();
	WorldPoint_Position.x = transform->Position.x + ViewScreen_Wide.x * LengthRate.x;
	WorldPoint_Position.y = transform->Position.y + ViewScreen_Wide.y * LengthRate.y * -1.0f;
	WorldPoint_Position.z = FarClip;

	printf("X: %f, Y: %f, Z: %f\n", WorldPoint_Position.x, WorldPoint_Position.y, WorldPoint_Position.z);

	std::array<std::list<GameObject*>, 4> SceneObjects = SceneManager::GetSceneObjectAll();
	//SceneObjects.

	// ----- ヒット処理の前準備 ----- //
	Vector3 RaySpeed = (WorldPoint_Position - transform->Position) * 0.01f;
	Vector3 RayPoint = transform->Position;
	Vector3 Late_RayPoint = transform->Position;
	bool IsHit = true;							// 当たったかどうかを表す
	std::list<GameObject*> HitObjects;			// 当たったオブジェクトを入れるためのリスト
	
	// ===== ヒット処理 ===== //
	do
	{
		// 進行方向に進める
		RayPoint += RaySpeed;

		// 各スレッド内のオブジェクトリスト取得
		for (int i = 1; i < SceneObjects.size(); i++)
		{
			// リスト内のオブジェクト取得
			for (auto& object : SceneObjects[i])
			{
				// 進む前と後の間にオブジェクトと当たった？
				if (CalculationHit::SegmentToHexahedron(Late_RayPoint, RayPoint, object->transform))
				{
					HitObjects.push_back(object);	// 当たったオブジェクトをリストに格納
					IsHit = false;					// 当たったことを伝える
				}
			}
		}

		// 現在の座標を代入
		Late_RayPoint = RayPoint;
	}
	// ①IsHitがtrue（オブジェクトと当たった）②進んだ距離がカメラの描画最遠距離より大きい
	// 上記のいずれかが当てはまれば、ループを抜ける
	while(IsHit && RayPoint.z < FarClip);

	if (HitObjects.empty())
		return nullptr;
	return HitObjects.front();
}
