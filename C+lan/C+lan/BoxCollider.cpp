// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
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
	// 自身の当たり判定の最小値を代入
	Vector3 myMinPoints = Vector3
	(
		transform->position.x - transform->scale.x / 2,
		transform->position.y - transform->scale.y / 2,
		transform->position.z - transform->scale.z / 2
	);

	// 自身の当たり判定の最大値を代入
	Vector3 myMaxPoints = Vector3
	(
		transform->position.x + transform->scale.x / 2,
		transform->position.y + transform->scale.y / 2,
		transform->position.z + transform->scale.z / 2
	);

	// 相手の当たり判定の最小値を代入
	Vector3 otherMinPoints = Vector3
	(
		other->transform->position.x - other->transform->scale.x / 2,
		other->transform->position.y - other->transform->scale.y / 2,
		other->transform->position.z - other->transform->scale.z / 2
	);

	// 相手の当たり判定の最大値を代入
	Vector3 otherMaxPoints = Vector3
	(
		other->transform->position.x + other->transform->scale.x / 2,
		other->transform->position.y + other->transform->scale.y / 2,
		other->transform->position.z + other->transform->scale.z / 2
	);

	// ===== 当たっているかどうか計算する処理 ===== //
	// 当たっていない場合returnでこの関数を抜ける
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
	// ここまで来たならオブジェクト同士は当たっている
	
	// 当たり判定が当たった場合の処理を行う関数を呼ぶ
	gameObject->HitCollision(other->gameObject);	// 自身用
	other->gameObject->HitCollision(gameObject);	// 相手用
}
