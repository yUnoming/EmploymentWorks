#include "Transform.h"
#include "renderer.h"

PublicSystem::Transform::Transform(const Transform* other)
{
	// �l���
	position = other->position;
	localPosition = other->localPosition;
	scale = other->scale;
	rotation = other->rotation;
}

void PublicSystem::Transform::Draw()
{
	// �e�����݂��Ȃ��H
	if (!parent)
		localPosition = position;	// ���[�J�����W�Ƀ��[���h���W����

	DirectX::SimpleMath::Matrix world = GetWorldMatrix(transform);	// ���[���h�s��擾
	Renderer::SetWorldMatrix(&world);								// ���[���h�s��Z�b�g
}

DirectX::SimpleMath::Matrix PublicSystem::Transform::GetWorldMatrix(Transform* childTransform)
{
	// �e�̍s��
	DirectX::SimpleMath::Matrix parentMatrix = DirectX::SimpleMath::Matrix::Identity;
	// �e�����݂���H
	if (parent)
	{
		parentMatrix = parent->transform->GetWorldMatrix(transform);	// �e�̃��[���h�s����擾
		childTransform->position += this->transform->localPosition;		// ���[���h���W�����Z
	}
	else
		childTransform->position = this->transform->position;			// �e�̃��[���h���W����

	// ���g�̃��[���h�s����v�Z
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
	// �������g�ł͂Ȃ��H
	if (this != &other && this)
	{
		// �l���
		position = other.position;
		localPosition = other.localPosition;
		scale = other.scale;
		rotation = other.rotation;
	}
	return *this;
}
