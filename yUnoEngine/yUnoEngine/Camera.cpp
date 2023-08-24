// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Camera.h"
#include "renderer.h"
#include "Transform.h"
#include <SimpleMath.h>

// ������������������������������ //
// �@�@		  using�錾		 �@�@ //
// ������������������������������ //
using namespace PublicSystem;


void PublicSystem::Camera::Draw()
{
	AddComponent<Transform>();
	// �r���[�ϊ��s��쐬
	DirectX::SimpleMath::Matrix ViewMatrix;

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 target = DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f);
	DirectX::XMFLOAT3 up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	position.x = transform->Position.x;
	position.y = transform->Position.y;
	position.z = transform->Position.z;

	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR Up = DirectX::XMLoadFloat3(&up);

	ViewMatrix = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);

	Renderer::SetViewMatrix(&ViewMatrix);
	
	//�v���W�F�N�V�����s��̐���
	float Fov = FieldOfView * 3.14159265f / 180.0f;
	float aspectRatio = static_cast<float>(960) / static_cast<float>(540);	// �A�X�y�N�g��	

	//�v���W�F�N�V�����s��̐���
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(Fov, aspectRatio, NearClip, FarClip);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}
