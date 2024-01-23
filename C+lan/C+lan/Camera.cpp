// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
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
	// �r���[�s�񐶐��ɕK�v�ȕϐ�
	DirectX::XMVECTOR eye = DirectX::XMLoadFloat3(&m_eye);
	DirectX::XMVECTOR focus = DirectX::XMLoadFloat3(&m_focus);
	DirectX::XMVECTOR up = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&m_up));
	DirectX::XMVECTOR front = DirectX::XMVectorSubtract(focus, eye);
	float focusLength;
	DirectX::XMStoreFloat(&focusLength, DirectX::XMVector3Length(front));
	front = DirectX::XMVector3Normalize(front);
	DirectX::XMVECTOR side = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up, front));
	up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(front, side));

	// �J������]
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

	// �r���[�s��̐���
	DirectX::SimpleMath::Matrix ViewMatrix;
	ViewMatrix = DirectX::XMMatrixLookAtLH(
		DirectX::XMLoadFloat3(&m_eye), DirectX::XMLoadFloat3(&m_focus), DirectX::XMLoadFloat3(&m_up));
	// �r���[�s����Z�b�g
	Renderer::SetViewMatrix(&ViewMatrix);
	
	//�v���W�F�N�V�����s��ɕK�v�ȕϐ�
	float Fov = fieldOfView * 3.14159265f / 180.0f;
	float aspectRatio = static_cast<float>(960) / static_cast<float>(540);	// �A�X�y�N�g��	

	//�v���W�F�N�V�����s��̐���
	DirectX::SimpleMath::Matrix projectionMatrix;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(Fov, aspectRatio, nearClip, farClip);
	//�v���W�F�N�V�����s����Z�b�g
	Renderer::SetProjectionMatrix(&projectionMatrix);
}

Ctlan::PrivateSystem::GameObject* Ctlan::PublicSystem::Camera::GetScreenPointObject(Vector2 screenPoint)
{
	// ===== �����Ŏ󂯎�����X�N���[�����W�����[���h���W�ɕϊ����鏈�� ===== //
	// �J�����̍ŉ��`��n�_�̕������߂�
	Vector2 ViewScreen_Wide = Vector2
		(
			farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f) * (960.0f / 540.0f),	// ����
			farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f)						// �c��
		);

	// �N���C�A���g�̈���擾
	RECT rect;
	GetClientRect(Ctlan::PrivateSystem::Application::GetWindow(), &rect);

	// �X�N���[���̒��S���W���v�Z
	Vector2 Screen_CenterPosition = Vector2(rect.right / 2, rect.bottom / 2);
	Vector2 Center_To_Point_Length = screenPoint - Screen_CenterPosition;
	Vector2 LengthRate = Center_To_Point_Length / Screen_CenterPosition;

	// �����̒l���J�����̍ŉ��`��n�_�̍��W�ʒu�Ɋ��蓖�Ă�
	DirectX::XMFLOAT3 worldPointPosition;
	worldPointPosition.x = transform->position.x + ViewScreen_Wide.x * LengthRate.x;
	worldPointPosition.y = transform->position.y + ViewScreen_Wide.y * LengthRate.y * -1.0f;
	worldPointPosition.z = farClip;

	// �J�����̉�]�ɍ��킹�Ĉʒu�𒲐�
	DirectX::XMMATRIX mtxRot =
	DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(transform->rotation.y)) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(transform->rotation.z));
	DirectX::XMFLOAT3 xmWorldPointPosition = DirectX::XMFLOAT3(worldPointPosition);
	DirectX::XMVECTOR rotatedWorldPointPosition = DirectX::XMLoadFloat3(&xmWorldPointPosition);
	rotatedWorldPointPosition = DirectX::XMVector3TransformCoord(rotatedWorldPointPosition, mtxRot);
	DirectX::XMStoreFloat3(&worldPointPosition, rotatedWorldPointPosition);

	// ----- �q�b�g�����̑O���� ----- //
	std::array<std::list<PrivateSystem::GameObject*>, 4> SceneObjects = SceneManager::GetSceneObjectAll();	// ���݃V�[�����̃I�u�W�F�N�g���	
	Vector3 raySpeed = (Vector3(worldPointPosition) - transform->position) * 0.001f;	// ���C�̑��x
	Vector3 rayPoint = transform->position;											// ���C�̈ړ���̍��W
	Vector3 lateRayPoint = transform->position;										// ���C�̈ړ��O�̍��W
	bool IsHit = false;																// �����������ǂ�����\��
	std::list<PrivateSystem::GameObject*> HitObjects;								// ���������I�u�W�F�N�g�����邽�߂̃��X�g

	// ===== �q�b�g���� ===== //
	do
	{
		// �i�s�����ɐi�߂�
		rayPoint += raySpeed;

		// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
		for (int i = 1; i < SceneObjects.size(); i++)
		{
			// ���X�g���̃I�u�W�F�N�g�擾
			for (auto& object : SceneObjects[i])
			{
				if (object->GetComponent<Text>())
				{
					Text text = *object->GetComponent<Text>();
					Vector3 rightTop = Vector3(text.leftTopPoint.x + text.fontSize.x * text.GetTextLength(), text.leftTopPoint.y + text.fontSize.y);
					Vector3 leftBottom = Vector3(text.leftTopPoint.x, text.leftTopPoint.y);
					// �e�L�X�g�ƃJ�[�\�����W���������Ă���H
					if (CalculationHit::PointToQuadrangle(screenPoint, rightTop, leftBottom))
					{
						HitObjects.push_front(object);	// ���������I�u�W�F�N�g�����X�g�Ɋi�[
						IsHit = true;					// �����������Ƃ�`����
					}
					continue;
				}
				else if (!object->isActive || !object->GetComponent<ModelRenderer>())
					continue;

				// ���_�f�[�^�擾
				std::vector<VERTEX_3D> vertices = object->GetComponent<ModelRenderer>()->GetModelVertices();
				DirectX::BoundingBox boundingBox;
				// ���_�f�[�^���狫�E�{�b�N�X���v�Z
				DirectX::BoundingBox::CreateFromPoints(
					boundingBox, vertices.size(), &vertices[0].Position, sizeof(VERTEX_3D)
				);

				// �i�ޑO�ƌ�̊ԂɃI�u�W�F�N�g�Ɠ��������H
				if (CalculationHit::SegmentToHexahedron(lateRayPoint, rayPoint, boundingBox, object->transform))
				{
					HitObjects.push_back(object);	// ���������I�u�W�F�N�g�����X�g�Ɋi�[
					IsHit = true;					// �����������Ƃ�`����
				}
			}
		}

		// ���݂̍��W����
		lateRayPoint = rayPoint;
	}
	// �@IsHit��true�i�I�u�W�F�N�g�Ɠ��������j�A�i�񂾋������J�����̕`��ŉ��������傫��
	// ��L�̂����ꂩ�����Ă͂܂�΁A���[�v�𔲂���
	while(!IsHit && ((rayPoint.z <= 0.0f && rayPoint.z > worldPointPosition.z) || (rayPoint.z >= 0.0f && rayPoint.z < worldPointPosition.z)));

	if (HitObjects.empty())
		return nullptr;
	return HitObjects.front();
}

Ctlan::PrivateSystem::GameObject* Ctlan::PublicSystem::Camera::GetScreenPointManipulator(Vector2 screenPoint)
{
	// ===== �����Ŏ󂯎�����X�N���[�����W�����[���h���W�ɕϊ����鏈�� ===== //
	// �J�����̍ŉ��`��n�_�̕������߂�
	Vector2 ViewScreen_Wide = Vector2
	(
		farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f) * (960.0f / 540.0f),	// ����
		farClip * tanf(fieldOfView / 2 * 3.14159265f / 180.0f)						// �c��
	);

	// �N���C�A���g�̈���擾
	RECT rect;
	GetClientRect(Ctlan::PrivateSystem::Application::GetWindow(), &rect);

	// �X�N���[���̒��S���W���v�Z
	Vector2 Screen_CenterPosition = Vector2(rect.right / 2, rect.bottom / 2);
	Vector2 Center_To_Point_Length = screenPoint - Screen_CenterPosition;
	Vector2 LengthRate = Center_To_Point_Length / Screen_CenterPosition;

	// �����̒l���J�����̍ŉ��`��n�_�̍��W�ʒu�Ɋ��蓖�Ă�
	DirectX::XMFLOAT3 worldPointPosition;
	worldPointPosition.x = transform->position.x + ViewScreen_Wide.x * LengthRate.x;
	worldPointPosition.y = transform->position.y + ViewScreen_Wide.y * LengthRate.y * -1.0f;
	worldPointPosition.z = farClip;

	// �J�����̉�]�ɍ��킹�Ĉʒu�𒲐�
	DirectX::XMMATRIX mtxRot =
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(transform->rotation.y)) * DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(transform->rotation.x));
	DirectX::XMFLOAT3 xmWorldPointPosition = DirectX::XMFLOAT3(worldPointPosition);
	DirectX::XMVECTOR rotatedWorldPointPosition = DirectX::XMLoadFloat3(&xmWorldPointPosition);
	rotatedWorldPointPosition = DirectX::XMVector3TransformCoord(rotatedWorldPointPosition, mtxRot);
	DirectX::XMStoreFloat3(&worldPointPosition, rotatedWorldPointPosition);

	// ----- �q�b�g�����̑O���� ----- //
	std::array<std::list<PrivateSystem::GameObject*>, 4> SceneObjects = SystemManager::SystemSceneManager::GetEditScene()->GetAllSceneObjects();	// ���݃V�[�����̃I�u�W�F�N�g���	
	Vector3 raySpeed = (Vector3(worldPointPosition) - transform->position) * 0.001f;	// ���C�̑��x
	Vector3 rayPoint = transform->position;											// ���C�̈ړ���̍��W
	Vector3 lateRayPoint = transform->position;										// ���C�̈ړ��O�̍��W
	bool IsHit = false;																// �����������ǂ�����\��
	std::list<PrivateSystem::GameObject*> HitObjects;								// ���������I�u�W�F�N�g�����邽�߂̃��X�g

	// ===== �q�b�g���� ===== //
	do
	{
		// �i�s�����ɐi�߂�
		rayPoint += raySpeed;

		// �e�X���b�h���̃I�u�W�F�N�g���X�g�擾
		for (int i = 1; i < SceneObjects.size(); i++)
		{
			// ���X�g���̃I�u�W�F�N�g�擾
			for (auto& object : SceneObjects[i])
			{
				if (!object->isActive)
					continue;
				if (object->GetComponent<Text>() || !object->GetComponent<ModelRenderer>())
					continue;

				// ���_�f�[�^�擾
				std::vector<VERTEX_3D> vertices = object->GetComponent<ModelRenderer>()->GetModelVertices();
				DirectX::BoundingBox boundingBox;
				// ���_�f�[�^���狫�E�{�b�N�X���v�Z
				DirectX::BoundingBox::CreateFromPoints(
					boundingBox, vertices.size(), &vertices[0].Position, sizeof(VERTEX_3D)
				);

				// �i�ޑO�ƌ�̊ԂɃI�u�W�F�N�g�Ɠ��������H
				if (CalculationHit::SegmentToHexahedron(lateRayPoint, rayPoint, boundingBox, object->transform))
				{
					HitObjects.push_back(object);	// ���������I�u�W�F�N�g�����X�g�Ɋi�[
					IsHit = true;					// �����������Ƃ�`����
				}
			}
		}

		// ���݂̍��W����
		lateRayPoint = rayPoint;
	}
	// �@IsHit��true�i�I�u�W�F�N�g�Ɠ��������j�A�i�񂾋������J�����̕`��ŉ��������傫��
	// ��L�̂����ꂩ�����Ă͂܂�΁A���[�v�𔲂���
	while (!IsHit && ((rayPoint.z <= 0.0f && rayPoint.z > worldPointPosition.z) || (rayPoint.z >= 0.0f && rayPoint.z < worldPointPosition.z)));

	if (HitObjects.empty())
		return nullptr;
	return HitObjects.front();
	}
