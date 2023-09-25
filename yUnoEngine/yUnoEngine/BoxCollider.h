#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"


class BoxCollider : public EachFunction
{
	public:
		// ----- variables / 変数 ----- //
		

		// ----- functions / 関数 ----- //
		void CalcCollision(BoxCollider *_ohter);	// 当たり判定の計算

};

