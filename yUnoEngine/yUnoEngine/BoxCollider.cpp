// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "BoxCollider.h"
#include "Transform.h"
#include "Vector3.h"


void BoxCollider::CalcCollision(BoxCollider *_ohter)
{
	// 自身の当たり判定の最小値を代入
	Vector3 My_MinPoints = Vector3
	(
		transform->Position.x - transform->Scale.x / 2,
		transform->Position.y - transform->Scale.y / 2,
		transform->Position.z - transform->Scale.z / 2
	);

	// 自身の当たり判定の最大値を代入
	Vector3 My_MaxPoints = Vector3
	(
		transform->Position.x + transform->Scale.x / 2,
		transform->Position.y + transform->Scale.y / 2,
		transform->Position.z + transform->Scale.z / 2
	);

	// 相手の当たり判定の最小値を代入
	Vector3 Other_MinPoints = Vector3
	(
		_ohter->transform->Position.x - _ohter->transform->Scale.x / 2,
		_ohter->transform->Position.y - _ohter->transform->Scale.y / 2,
		_ohter->transform->Position.z - _ohter->transform->Scale.z / 2
	);

	// 相手の当たり判定の最大値を代入
	Vector3 Other_MaxPoints = Vector3
	(
		_ohter->transform->Position.x + _ohter->transform->Scale.x / 2,
		_ohter->transform->Position.y + _ohter->transform->Scale.y / 2,
		_ohter->transform->Position.z + _ohter->transform->Scale.z / 2
	);

	// ===== 当たっているかどうか計算する処理 ===== //
	// 当たっていない場合returnでこの関数を抜ける
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
	// ここまで来たならオブジェクト同士は当たっている
	
	// 当たり判定が当たった場合の処理を行う関数を呼ぶ
	Myself->HitCollision();			// 自身用
	_ohter->Myself->HitCollision();	// 相手用
}
