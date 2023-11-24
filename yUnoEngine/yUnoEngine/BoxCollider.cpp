// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "BoxCollider.h"
#include "Transform.h"
#include "Vector3.h"


void BoxCollider::CalcCollision(BoxCollider *ohter)
{
	// 自身の当たり判定の最小値を代入
	Vector3 myMinPoints = Vector3
	(
		transform->Position.x - transform->Scale.x / 2,
		transform->Position.y - transform->Scale.y / 2,
		transform->Position.z - transform->Scale.z / 2
	);

	// 自身の当たり判定の最大値を代入
	Vector3 myMaxPoints = Vector3
	(
		transform->Position.x + transform->Scale.x / 2,
		transform->Position.y + transform->Scale.y / 2,
		transform->Position.z + transform->Scale.z / 2
	);

	// 相手の当たり判定の最小値を代入
	Vector3 otherMinPoints = Vector3
	(
		ohter->transform->Position.x - ohter->transform->Scale.x / 2,
		ohter->transform->Position.y - ohter->transform->Scale.y / 2,
		ohter->transform->Position.z - ohter->transform->Scale.z / 2
	);

	// 相手の当たり判定の最大値を代入
	Vector3 otherMaxPoints = Vector3
	(
		ohter->transform->Position.x + ohter->transform->Scale.x / 2,
		ohter->transform->Position.y + ohter->transform->Scale.y / 2,
		ohter->transform->Position.z + ohter->transform->Scale.z / 2
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
	gameObject->HitCollision();			// 自身用
	ohter->gameObject->HitCollision();	// 相手用
}
