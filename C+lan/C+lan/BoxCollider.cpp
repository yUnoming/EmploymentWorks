// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "BoxCollider.h"
#include "Transform.h"
#include "Vector3.h"

#include "SystemCollisionManager.h"


Ctlan::PublicSystem::BoxCollider::~BoxCollider()
{
	PrivateSystem::SystemManager::SystemCollisionManager::Erase(this);
}

void Ctlan::PublicSystem::BoxCollider::CalcCollision(BoxCollider *other)
{
	// ���g�̓����蔻��̍ŏ��l����
	Vector3 myMinPoints = Vector3
	(
		transform->position.x - transform->scale.x / 2,
		transform->position.y - transform->scale.y / 2,
		transform->position.z - transform->scale.z / 2
	);

	// ���g�̓����蔻��̍ő�l����
	Vector3 myMaxPoints = Vector3
	(
		transform->position.x + transform->scale.x / 2,
		transform->position.y + transform->scale.y / 2,
		transform->position.z + transform->scale.z / 2
	);

	// ����̓����蔻��̍ŏ��l����
	Vector3 otherMinPoints = Vector3
	(
		other->transform->position.x - other->transform->scale.x / 2,
		other->transform->position.y - other->transform->scale.y / 2,
		other->transform->position.z - other->transform->scale.z / 2
	);

	// ����̓����蔻��̍ő�l����
	Vector3 otherMaxPoints = Vector3
	(
		other->transform->position.x + other->transform->scale.x / 2,
		other->transform->position.y + other->transform->scale.y / 2,
		other->transform->position.z + other->transform->scale.z / 2
	);

	// ===== �������Ă��邩�ǂ����v�Z���鏈�� ===== //
	// �������Ă��Ȃ��ꍇreturn�ł��̊֐��𔲂���
	if (myMaxPoints.x < otherMinPoints.x)
		return;
	if (myMaxPoints.y < otherMinPoints.y)
		return;
	if (myMaxPoints.z < otherMinPoints.z)
		return;
	if (myMinPoints.x > otherMaxPoints.x)
		return;
	if (myMinPoints.y > otherMaxPoints.y)
		return;
	if (myMinPoints.z > otherMaxPoints.z)
		return;

	////////////////////////////////////////////////////
	// �����܂ŗ����Ȃ�I�u�W�F�N�g���m�͓������Ă���
	
	// �����蔻�肪���������ꍇ�̏������s���֐����Ă�
	gameObject->HitCollision(other->gameObject);	// ���g�p
	other->gameObject->HitCollision(gameObject);	// ����p
}
