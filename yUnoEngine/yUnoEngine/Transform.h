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
#include <SimpleMath.h>

namespace PublicSystem
{
	/// <summary>
	///	�ʒu�E��]�E�傫����\���N���X	</summary>
	class Transform : public EachFunction
	{
	public:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		/// ���[���h���W	</summary>
		Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		/// ���[�J�����W	</summary>
		Vector3 localPosition = Vector3(0.0f, 0.0f, 0.0f);

		/// <summary>
		/// ��]	</summary>
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		///	�傫��	</summary>
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);

		// ----- functions / �֐� ----- //
		/// <summary>
		///	�`�揈��	</summary>
		void Draw();
		/// <summary>
		/// ���[���h�s����擾	</summary>
		/// <returns>���[���h�s��</returns>
		DirectX::SimpleMath::Matrix GetWorldMatrix(Transform* childTransform);
	};
}

