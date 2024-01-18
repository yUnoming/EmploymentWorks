#include "Transform.h"
#include "renderer.h"

PublicSystem::Transform::Transform(const Transform* other)
{
	// 値代入
	position = other->position;
	localPosition = other->localPosition;
	scale = other->scale;
	rotation = other->rotation;
}

void PublicSystem::Transform::Draw()
{
	// 親が存在しない？
	if (!parent)
		localPosition = position;	// ローカル座標にワールド座標を代入

	DirectX::SimpleMath::Matrix world = GetWorldMatrix(transform);	// ワールド行列取得
	Renderer::SetWorldMatrix(&world);								// ワールド行列セット
}

DirectX::SimpleMath::Matrix PublicSystem::Transform::GetWorldMatrix(Transform* childTransform)
{
	// 親の行列
	DirectX::SimpleMath::Matrix parentMatrix = DirectX::SimpleMath::Matrix::Identity;
	// 親が存在する？
	if (parent)
	{
		parentMatrix = parent->transform->GetWorldMatrix(transform);	// 親のワールド行列を取得
		childTransform->position += this->transform->localPosition;		// ワールド座標を加算
	}
	else
		childTransform->position = this->transform->position;			// 親のワールド座標を代入

	// 自身のワールド行列を計算
	DirectX::SimpleMath::Matrix world, trans, rot, scl;
	trans = DirectX::SimpleMath::Matrix::CreateTranslation(transform->localPosition.x, transform->localPosition.y, transform->localPosition.z);
	rot = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(
		DirectX::XMConvertToRadians(transform->rotation.y), 
		DirectX::XMConvertToRadians(transform->rotation.x),
		DirectX::XMConvertToRadians(transform->rotation.z));
	scl = DirectX::SimpleMath::Matrix::CreateScale(transform->scale.x, transform->scale.y, transform->scale.z);
	world = scl * rot * trans * parentMatrix;

	return world;
}

Transform& PublicSystem::Transform::operator=(const Transform& other)
{
	// 自分自身ではない？
	if (this != &other && this)
	{
		// 値代入
		position = other.position;
		localPosition = other.localPosition;
		scale = other.scale;
		rotation = other.rotation;
	}
	return *this;
}
