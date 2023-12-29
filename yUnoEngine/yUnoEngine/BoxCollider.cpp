// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "BoxCollider.h"
#include "Transform.h"
#include "Vector3.h"


void BoxCollider::CalcCollision(BoxCollider *ohter)
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
		ohter->transform->position.x - ohter->transform->scale.x / 2,
		ohter->transform->position.y - ohter->transform->scale.y / 2,
		ohter->transform->position.z - ohter->transform->scale.z / 2
	);

	// ����̓����蔻��̍ő�l����
	Vector3 otherMaxPoints = Vector3
	(
		ohter->transform->position.x + ohter->transform->scale.x / 2,
		ohter->transform->position.y + ohter->transform->scale.y / 2,
		ohter->transform->position.z + ohter->transform->scale.z / 2
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
	gameObject->HitCollision();			// ���g�p
	ohter->gameObject->HitCollision();	// ����p
}
