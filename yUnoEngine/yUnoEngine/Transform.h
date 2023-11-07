#pragma once
/**
* @file		Transform.h
* @brief	Transform�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.02
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "Vector3.h"


namespace PublicSystem
{
	/// <summary>
	///	�ʒu�E��]�E�傫����\���N���X	</summary>
	class Transform : public EachFunction
	{
	public:

		// ----- variables / �ϐ� ----- //
		/// <summary>
		/// �ʒu	</summary>
		Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		/// ��]	</summary>
		Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		///	�傫��	</summary>
		Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);
	};
}

