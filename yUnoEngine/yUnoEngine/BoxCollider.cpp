// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "BoxCollider.h"
#include "Transform.h"
#include "Vector3.h"


void BoxCollider::CalcCollision(BoxCollider *_ohter)
{
	// ���g�̓����蔻��̍ŏ��l����
	Vector3 My_MinPoints = Vector3
	(
		transform->Position.x - transform->Scale.x / 2,
		transform->Position.y - transform->Scale.y / 2,
		transform->Position.z - transform->Scale.z / 2
	);

	// ���g�̓����蔻��̍ő�l����
	Vector3 My_MaxPoints = Vector3
	(
		transform->Position.x + transform->Scale.x / 2,
		transform->Position.y + transform->Scale.y / 2,
		transform->Position.z + transform->Scale.z / 2
	);

	// ����̓����蔻��̍ŏ��l����
	Vector3 Other_MinPoints = Vector3
	(
		_ohter->transform->Position.x - _ohter->transform->Scale.x / 2,
		_ohter->transform->Position.y - _ohter->transform->Scale.y / 2,
		_ohter->transform->Position.z - _ohter->transform->Scale.z / 2
	);

	// ����̓����蔻��̍ő�l����
	Vector3 Other_MaxPoints = Vector3
	(
		_ohter->transform->Position.x + _ohter->transform->Scale.x / 2,
		_ohter->transform->Position.y + _ohter->transform->Scale.y / 2,
		_ohter->transform->Position.z + _ohter->transform->Scale.z / 2
	);

	// ===== �������Ă��邩�ǂ����v�Z���鏈�� ===== //
	// �������Ă��Ȃ��ꍇreturn�ł��̊֐��𔲂���
	if (My_MaxPoints.x < Other_MinPoints.x)
		return;
	if (My_MaxPoints.y < Other_MinPoints.y)
		return;
	if (My_MaxPoints.z < Other_MinPoints.z)
		return;
	if (My_MinPoints.x > Other_MaxPoints.x)
		return;
	if (My_MinPoints.y > Other_MaxPoints.y)
		return;
	if (My_MinPoints.z > Other_MaxPoints.z)
		return;

	////////////////////////////////////////////////////
	// �����܂ŗ����Ȃ�I�u�W�F�N�g���m�͓������Ă���
	
	// �����蔻�肪���������ꍇ�̏������s���֐����Ă�
	Myself->HitCollision();			// ���g�p
	_ohter->Myself->HitCollision();	// ����p
}
