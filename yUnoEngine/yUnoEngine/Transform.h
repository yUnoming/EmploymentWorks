#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "Vector3.h"

using namespace PublicSystem;

class Transform : public EachFunction
{
	public:

		// ----- variables / 変数 ----- //
		Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);	// 位置
		Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);	// 回転
		Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);		// 大きさ
};


namespace PublicSystem
{

}

