#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"


class BoxCollider : public EachFunction
{
	public:
		// ----- variables / �ϐ� ----- //
		

		// ----- functions / �֐� ----- //
		void CalcCollision(BoxCollider *_ohter);	// �����蔻��̌v�Z

};

