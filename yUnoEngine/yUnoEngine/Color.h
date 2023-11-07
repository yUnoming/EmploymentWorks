#pragma once
/**
* @file		Color.h
* @brief	Color�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.05
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <DirectXMath.h>


namespace PublicSystem
{
	/// <summary>
	///	�F�irgba�j��\���N���X	</summary>
	class Color
	{
		public:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			///	Red / ��	</summary>
			float r = 1.0f;
			/// <summary>
			///	Green / ��	</summary>
			float g = 1.0f;
			/// <summary>
			///	Blue / ��	</summary>
			float b = 1.0f;
			/// <summary>
			///	Alpha / �����x	</summary>
			float a = 1.0f;


			// ----- functions / �֐� ----- //
			/// <summary>
			/// �ʏ�R���X�g���N�^	</summary>
			Color() {};
			/// <summary>
			/// �����t���R���X�g���N�^	</summary>
			///<param name = "r">
			/// �ԐF�̋���	</param>
			///<param name = "g">
			/// �ΐF�̋���	</param>
			///<param name = "b">
			/// �F�̋���	</param>
			///<param name = "a">
			/// �����x�̋���	</param>
			Color(float r, float g, float b, float a);


			// ----- �L���X�g���Z�q ----- //
			// **  XMFLOAT4  ** //
			operator DirectX::XMFLOAT4() const;


	};
}

