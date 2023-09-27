#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <DirectXMath.h>


namespace PublicSystem
{
	// �F�irgba�j��\���N���X
	class Color
	{
		public:
			// ----- variables / �ϐ� ----- //
			float r = 1.0f;		//   Red / ��
			float g = 1.0f;		// Green / ��
			float b = 1.0f;		//  Blue / ��
			float a = 1.0f;		// Alpha / �����x


			// ----- functions / �֐� ----- //
			/// <summary>
			/// �ʏ�R���X�g���N�^	</summary>
			Color() {};
			/// <summary>
			/// �e�l�ɑ�����s����R���X�g���N�^	</summary>
			///<param name = "_r">
			/// �^�ԐF�̋���	</param>
			///<param name = "_g">
			/// �^�ΐF�̋���	</param>
			///<param name = "_b">
			/// �^�F�̋���	</param>
			///<param name = "_a">
			/// �^�����x�̋���	</param>
			Color(float _r, float _g, float _b, float _a);


			// ----- �L���X�g���Z�q ----- //
			// **  XMFLOAT4  ** //
			operator DirectX::XMFLOAT4() const;


	};
}

