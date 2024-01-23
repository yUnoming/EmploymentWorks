// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Camera.h"
#include "renderer.h"
#include "Transform.h"
#include "modelRenderer.h"
#include <math.h>
#include <SimpleMath.h>
#include <algorithm>
#include "SceneManager.h"
#include "CalculationHit.h"
#include "Text.h"
#include "SystemSceneManager.h"


void Ctlan::PublicSystem::Camera::Init()
{
	m_eye = transform->position;
	m_focus = DirectX::XMFLOAT3(transform->position.x, transform->position.y, transform->position.z + 10.0f);
	m_up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
}

void Ctlan::PublicSystem::Camera::Draw()
{
	// ビュー行列生成に必要な変数
	DirectX::XMVECTOR eye = DirectX::XMLoadFloat3(&m_eye);
	DirectX::XMVECTOR focus = DirectX::XMLoadFloat3(&m_focus);
	DirectX::XMVECTOR up = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&m_up));
	DirectX::XMVECTOR front = DirectX::XMVectorSubtract(focus, eye);
	float focusLength;
	DirectX::XMStoreFloat(&focusLength, DirectX::XMVector3Length(front));
	front = DirectX::XMVector3Normalize(front);
	DirectX::XMVECTOR side = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up, front));
	up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(front, side));

	// カメラ回転
	if (lateRotation.x != transform->rotation.x || lateRotation.y != transform->rotation.y)
	{
		Vector3 rotAngle = Vector3(transform->rotation - lateRotation);

		DirectX::XMMATRIX mtxRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(rotAngle.y));
		DirectX::XMVECTOR sideAxis = DirectX::XMVector3Normalize(DirectX::XMVector3TransformCoord(side, mtxRotY));

		DirectX::XMMATRIX mtxRotX = DirectX::XMMatrixRotationAxis(sideAxis, DirectX::XMConvertToRadians(rotAngle.x));
		DirectX::XMVECTOR frontAxis = DirectX::XMVector3Normalize(DirectX::XMVector3TransformCoord(front, mtxRotY * mtxRotX));

		DirectX::XMVECTOR camEye = DirectX::XMVectorZero();
		camEye = DirectX::XMVectorScale(camEye, 0.1f);

		DirectX::XMStoreFloat3(&m_eye, DirectX::XMVectorAdd(eye, camEye));
		DirectX::XMStoreFloat3(&m_focus, DirectX::XMVectorAdd(eye, DirectX::XMVectorScale(frontAxis, focusLength)));
		DirectX::XMStoreFloat3(&m_up, DirectX::XMVector3Normalize(DirectX::XMVector3Cross(frontAxis, sideAxis)));
	}

	lateRotation = transform->rotation;

	// ビュー行列の生成
	DirectX::SimpleMath::Matrix ViewMatrix;
	ViewMatrix = DirectX::XMMatrixLookAtLH(
		DirectX::XMLoadFloat3(&m_eye), DirectX::XMLoadFloat3(&m_focus), DirectX::XMLoadFloat3(&m_up));
	// ビュー行列をセット
	Renderer::SetViewMatrix(&ViewMatrix);
	
	//プロジェクション行列に必要な変数
	float Fov = fieldOfView * 3.14159265f / 180.0f;
	float aspectRatio = static_cast<float>(960) / static_cast<float>(540);	// アスペクト比	

	//プロジェクション行列の生成
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(Fov, aspectRatio, nearClip, farClip);
	//プロジェクション行列をセット
	Renderer::SetProjectionMatrix(&projectionMatrix);
}

Ctlan::PrivateSystem::GameObject* Ctlan::PublicSystem::Camera::GetScreenPointObject(Vector2 screenPoint)
{
	// ===== 引数で受け取ったスクリーン座標をワールド座標に変換する処理 ===== //
	// カメラの最遠描画地点の幅を求める
	Vector2 ViewScreen_Wide = Vector2
		(
			farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f) * (960.0f / 540.0f),	// 横幅
			farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f)						// 縦幅
		);

	// クライアント領域を取得
	RECT rect;
	GetClientRect(Ctlan::PrivateSystem::Application::GetWindow(), &rect);

	// スクリーンの中心座標を計算
	Vector2 Screen_CenterPosition = Vector2(rect.right / 2, rect.bottom / 2);
	Vector2 Center_To_Point_Length = screenPoint - Screen_CenterPosition;
	Vector2 LengthRate = Center_To_Point_Length / Screen_CenterPosition;

	// 引数の値をカメラの最遠描画地点の座標位置に割り当てる
	DirectX::XMFLOAT3 worldPointPosition;
	worldPointPosition.x = transform->position.x + ViewScreen_Wide.x * LengthRate.x;
	worldPointPosition.y = transform->position.y + ViewScreen_Wide.y * LengthRate.y * -1.0f;
	worldPointPosition.z = farClip;

	// カメラの回転に合わせて位置を調整
	DirectX::XMMATRIX mtxRot =
	DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(transform->rotation.y)) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(transform->rotation.z));
	DirectX::XMFLOAT3 xmWorldPointPosition = DirectX::XMFLOAT3(worldPointPosition);
	DirectX::XMVECTOR rotatedWorldPointPosition = DirectX::XMLoadFloat3(&xmWorldPointPosition);
	rotatedWorldPointPosition = DirectX::XMVector3TransformCoord(rotatedWorldPointPosition, mtxRot);
	DirectX::XMStoreFloat3(&worldPointPosition, rotatedWorldPointPosition);

	// ----- ヒット処理の前準備 ----- //
	std::array<std::list<PrivateSystem::GameObject*>, 4> SceneObjects = SceneManager::GetSceneObjectAll();	// 現在シーン内のオブジェクト情報	
	Vector3 raySpeed = (Vector3(worldPointPosition) - transform->position) * 0.001f;	// レイの速度
	Vector3 rayPoint = transform->position;											// レイの移動後の座標
	Vector3 lateRayPoint = transform->position;										// レイの移動前の座標
	bool IsHit = false;																// 当たったかどうかを表す
	std::list<PrivateSystem::GameObject*> HitObjects;								// 当たったオブジェクトを入れるためのリスト

	// ===== ヒット処理 ===== //
	do
	{
		// 進行方向に進める
		rayPoint += raySpeed;

		// 各スレッド内のオブジェクトリスト取得
		for (int i = 1; i < SceneObjects.size(); i++)
		{
			// リスト内のオブジェクト取得
			for (auto& object : SceneObjects[i])
			{
				if (object->GetComponent<Text>())
				{
					Text text = *object->GetComponent<Text>();
					Vector3 rightTop = Vector3(text.leftTopPoint.x + text.fontSize.x * text.GetTextLength(), text.leftTopPoint.y + text.fontSize.y);
					Vector3 leftBottom = Vector3(text.leftTopPoint.x, text.leftTopPoint.y);
					// テキストとカーソル座標が当たっている？
					if (CalculationHit::PointToQuadrangle(screenPoint, rightTop, leftBottom))
					{
						HitObjects.push_front(object);	// 当たったオブジェクトをリストに格納
						IsHit = true;					// 当たったことを伝える
					}
					continue;
				}
				else if (!object->isActive || !object->GetComponent<ModelRenderer>())
					continue;

				// 頂点データ取得
				std::vector<VERTEX_3D> vertices = object->GetComponent<ModelRenderer>()->GetModelVertices();
				DirectX::BoundingBox boundingBox;
				// 頂点データから境界ボックスを計算
				DirectX::BoundingBox::CreateFromPoints(
					boundingBox, vertices.size(), &vertices[0].Position, sizeof(VERTEX_3D)
				);

				// 進む前と後の間にオブジェクトと当たった？
				if (CalculationHit::SegmentToHexahedron(lateRayPoint, rayPoint, boundingBox, object->transform))
				{
					HitObjects.push_back(object);	// 当たったオブジェクトをリストに格納
					IsHit = true;					// 当たったことを伝える
				}
			}
		}

		// 現在の座標を代入
		lateRayPoint = rayPoint;
	}
	// ①IsHitがtrue（オブジェクトと当たった）②進んだ距離がカメラの描画最遠距離より大きい
	// 上記のいずれかが当てはまれば、ループを抜ける
	while(!IsHit && ((rayPoint.z <= 0.0f && rayPoint.z > worldPointPosition.z) || (rayPoint.z >= 0.0f && rayPoint.z < worldPointPosition.z)));

	if (HitObjects.empty())
		return nullptr;
	return HitObjects.front();
}

Ctlan::PrivateSystem::GameObject* Ctlan::PublicSystem::Camera::GetScreenPointManipulator(Vector2 screenPoint)
{
	// ===== 引数で受け取ったスクリーン座標をワールド座標に変換する処理 ===== //
	// カメラの最遠描画地点の幅を求める
	Vector2 ViewScreen_Wide = Vector2
	(
		farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f) * (960.0f / 540.0f),	// 横幅
		farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f)						// 縦幅
	);

	// クライアント領域を取得
	RECT rect;
	GetClientRect(Ctlan::PrivateSystem::Application::GetWindow(), &rect);

	// スクリーンの中心座標を計算
	Vector2 Screen_CenterPosition = Vector2(rect.right / 2, rect.bottom / 2);
	Vector2 Center_To_Point_Length = screenPoint - Screen_CenterPosition;
	Vector2 LengthRate = Center_To_Point_Length / Screen_CenterPosition;

	// 引数の値をカメラの最遠描画地点の座標位置に割り当てる
	DirectX::XMFLOAT3 worldPointPosition;
	worldPointPosition.x = transform->position.x + ViewScreen_Wide.x * LengthRate.x;
	worldPointPosition.y = transform->position.y + ViewScreen_Wide.y * LengthRate.y * -1.0f;
	worldPointPosition.z = farClip;

	// カメラの回転に合わせて位置を調整
	DirectX::XMMATRIX mtxRot =
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(transform->rotation.y)) * DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x));
	DirectX::XMFLOAT3 xmWorldPointPosition = DirectX::XMFLOAT3(worldPointPosition);
	DirectX::XMVECTOR rotatedWorldPointPosition = DirectX::XMLoadFloat3(&xmWorldPointPosition);
	rotatedWorldPointPosition = DirectX::XMVector3TransformCoord(rotatedWorldPointPosition, mtxRot);
	DirectX::XMStoreFloat3(&worldPointPosition, rotatedWorldPointPosition);

	// ----- ヒット処理の前準備 ----- //
	std::array<std::list<PrivateSystem::GameObject*>, 4> SceneObjects = SystemManager::SystemSceneManager::GetEditScene()->GetAllSceneObjects();	// 現在シーン内のオブジェクト情報	
	Vector3 raySpeed = (Vector3(worldPointPosition) - transform->position) * 0.001f;	// レイの速度
	Vector3 rayPoint = transform->position;											// レイの移動後の座標
	Vector3 lateRayPoint = transform->position;										// レイの移動前の座標
	bool IsHit = false;																// 当たったかどうかを表す
	std::list<PrivateSystem::GameObject*> HitObjects;								// 当たったオブジェクトを入れるためのリスト

	// ===== ヒット処理 ===== //
	do
	{
		// 進行方向に進める
		rayPoint += raySpeed;

		// 各スレッド内のオブジェクトリスト取得
		for (int i = 1; i < SceneObjects.size(); i++)
		{
			// リスト内のオブジェクト取得
			for (auto& object : SceneObjects[i])
			{
				if (!object->isActive)
					continue;
				if (object->GetComponent<Text>() || !object->GetComponent<ModelRenderer>())
					continue;

				// 頂点データ取得
				std::vector<VERTEX_3D> vertices = object->GetComponent<ModelRenderer>()->GetModelVertices();
				DirectX::BoundingBox boundingBox;
				// 頂点データから境界ボックスを計算
				DirectX::BoundingBox::CreateFromPoints(
					boundingBox, vertices.size(), &vertices[0].Position, sizeof(VERTEX_3D)
				);

				// 進む前と後の間にオブジェクトと当たった？
				if (CalculationHit::SegmentToHexahedron(lateRayPoint, rayPoint, boundingBox, object->transform))
				{
					HitObjects.push_back(object);	// 当たったオブジェクトをリストに格納
					IsHit = true;					// 当たったことを伝える
				}
			}
		}

		// 現在の座標を代入
		lateRayPoint = rayPoint;
	}
	// ①IsHitがtrue（オブジェクトと当たった）②進んだ距離がカメラの描画最遠距離より大きい
	// 上記のいずれかが当てはまれば、ループを抜ける
	while (!IsHit && ((rayPoint.z <= 0.0f && rayPoint.z > worldPointPosition.z) || (rayPoint.z >= 0.0f && rayPoint.z < worldPointPosition.z)));

	if (HitObjects.empty())
		return nullptr;
	return HitObjects.front();
	}
