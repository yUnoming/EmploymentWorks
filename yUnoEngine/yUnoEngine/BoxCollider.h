#pragma once
/**
* @file		BoxCollider.h
* @brief	BoxCollider�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"

/// <summary>
///	�{�b�N�X��̓����蔻��N���X	</summary>
class BoxCollider : public EachFunction
{
	public:
		// ----- functions / �֐� ----- //
		/// <summary>
		/// �����蔻��̌v�Z	</summary>
		/// <param name="other">
		/// �Փ˂�������̓����蔻��	</param>
		void CalcCollision(BoxCollider* other);

};

