#pragma once
/**
* @file		Vector3.h
* @brief	Vector3�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <DirectXMath.h>

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	�R�����̃x�N�g����\���N���X	</summary>
		class Vector3
		{
			public:
				// ----- variables / �ϐ� ----- //
				/// <summary>
				///	x���W	</summary>
				float x = 1.0f;
				/// <summary>
				///	y���W	</summary>
				float y = 1.0f;
				/// <summary>
				///	z���W	</summary>
				float z = 1.0f;


				// ----- functions / �֐� ----- //
				/// <summary>
				///	�R���X�g���N�^	</summary>
				Vector3() {};
				/// <summary>
				///	�����t���R���X�g���N�^	</summary>
				/// <param name="x">
				///	x���W�l	</param>
				/// <param name="y">
				/// y���W�l	</param>
				/// <param name="z">
				/// z���W�l	</param>
				Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
				/// <summary>
				/// �����t���R���X�g���N�^
				/// </summary>
				/// <param name="x">
				/// x���W�l	</param>
				/// <param name="y">
				/// y���W�l	</param>
				Vector3(float x, float y) : x(x), y(y) {};
				virtual ~Vector3() {};


				// ----- ���Z�q�̃I�[�o�[���[�h�Q ----- //
				//**  assignment / ���  **//
				/// <summary>
				///	Vector3�^�Ƃ̑���p�I�y���[�^�[	</summary>
				/// <param name="vec">
				///	Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̑������	</returns>
				Vector3 operator=(const Vector3& vec);
				/// <summary>
				///	DirectX::XMFLOAT3�^�Ƃ̑���p�I�y���[�^�[	</summary>
				/// <param name="vec">
				///	DirectX::XMFLOAT3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̑������	</returns>
				Vector3 operator=(const DirectX::XMFLOAT3& vec);

				//**  addition / ���Z  **//
				/// <summary>
				///	int�^�Ƃ̉��Z�p�I�y���[�^�[	</summary>
				/// <param name="i">
				/// int�l	</param>
				/// <returns>
				///	�l�̉��Z����	</returns>
				Vector3 operator+(int i);
				/// <summary>
			///	float�^�Ƃ̉��Z�p�I�y���[�^�[	</summary>
			/// <param name="f">
			///	float�l	</param>
			/// <returns>
			///	�l�̉��Z����	</returns>
				Vector3 operator+(float f);
				/// <summary>
				///	Vector3�^�Ƃ̉��Z�p�I�y���[�^�[	</summary>
				/// <param name="vec">
				/// Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̉��Z����	</returns>
				Vector3 operator+(const Vector3& vec);

				//**  add assignment / ���Z���  **//
				/// <summary>
				///	int�^�Ƃ̉��Z����p�I�y���[�^�[		</summary>
				/// <param name="i">
				/// int�l	</param>
				/// <returns>
				/// �l�̉��Z�������	</returns>
				Vector3 operator+=(int i);
				/// <summary>
				///	float�^�Ƃ̉��Z����p�I�y���[�^�[	</summary>
				/// <param name="f">
				///	float�l	</param>
				/// <returns>
				/// �l�̉��Z�������	</returns>
				Vector3 operator+=(float f);
				/// <summary>
				///	Vector3�^�Ƃ̉��Z����p�I�y���[�^�[	</summary>
				/// <param name="vec">
				///	Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				///	�l�̉��Z�������	</returns>
				Vector3 operator+=(const Vector3& vec);
				/// <summary>
				///	DirectX::XMFLOAT3�^�Ƃ̉��Z����p�I�y���[�^�[	</summary>
				/// <param name="vec">
				///	DirectX::XMFLOAT3�^�I�u�W�F�N�g	</param>
				/// <returns>
				///	�l�̉��Z�������	</returns>
				Vector3 operator+=(const DirectX::XMFLOAT3& vec);

				//**  subtraction / ���Z  **//
				/// <summary>
				///	int�^�Ƃ̌��Z�p�I�y���[�^�[	</summary>
				/// <param name="i">
				/// int�l	</param>
				/// <returns>
				///	�l�̌��Z����	</returns>
				Vector3 operator-(int i);
				/// <summary>
				///	float�^�Ƃ̌��Z�p�I�y���[�^�[	</summary>
				/// <param name="f">
				///	float�l	</param>
				/// <returns>
				///	�l�̌��Z����	</returns>
				Vector3 operator-(float f);
				/// <summary>
				/// Vector3�^�Ƃ̌��Z�p�I�y���[�^�[
				/// </summary>
				/// <param name="vec">
				///	Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̌��Z����	</returns>
				Vector3 operator-(const Vector3& vec);

				//**  sub assignment / ���Z���  **//
				/// <summary>
				///	int�^�Ƃ̌��Z����p�I�y���[�^�[		</summary>
				/// <param name="i">
				///	int�l	</param>
				/// <returns>
				/// �l�̌��Z�������	</returns>
				Vector3 operator-=(int i);
				/// <summary>
				/// float�^�Ƃ̌��Z����p�I�y���[�^�[
				/// </summary>
				/// <param name="f">
				/// float�l	</param>
				/// <returns>
				/// �l�̌��Z�������	</returns>
				Vector3 operator-=(float f);
				/// <summary>
				///	Vector3�^�Ƃ̌��Z����p�I�y���[�^�[	</summary>
				/// <param name="vec">
				///	Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̌��Z�������	</returns>
				Vector3 operator-=(const Vector3& vec);

				//** multiplication / ��Z  **//
				/// <summary>
				///	int�^�Ƃ̏�Z�p�I�y���[�^�[	</summary>
				/// <param name="i">
				///	int�l	</param>
				/// <returns>
				/// �l�̏�Z����	</returns>
				Vector3 operator*(int i);
				/// <summary>
				///	float�^�Ƃ̏�Z�p�I�y���[�^�[	</summary>
				/// <param name="f">
				/// float�l	</param>
				/// <returns>
				/// �l�̏�Z����	</returns>
				Vector3 operator*(float f);
				/// <summary>
				/// Vector3�^�Ƃ̏�Z�p�I�y���[�^�[	</summary>
				/// <param name="vec">
				///	Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				///	�l�̏�Z����	</returns>
				Vector3 operator*(const Vector3& vec);

				//**  multi assignment / ��Z���  **//
				/// <summary>
				///	int�^�̏�Z����p�I�y���[�^�[	</summary>
				/// <param name="i">
				/// int�l	</param>
				/// <returns>
				/// �l�̏�Z�������	</returns>
				Vector3 operator*=(int i);
				/// <summary>
				///	float�^�Ƃ̏�Z����p�I�y���[�^�[	</summary>
				/// <param name="f">
				///	float�l	</param>
				/// <returns>
				/// �l�̏�Z�������	</returns>
				Vector3 operator*=(float f);
				/// <summary>
				/// Vector3�^�Ƃ̏�Z����p�I�y���[�^�[		</summary>
				/// <param name="vec">
				///	Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̏�Z�������	</returns>
				Vector3 operator*=(const Vector3& vec);
				/// <summary>
				/// DirectX::XMFLOAT3�^�Ƃ̏�Z����p�I�y���[�^�[		</summary>
				/// <param name="vec">
				///	DirectX::XMFLOAT3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̏�Z�������	</returns>
				Vector3 operator*=(const DirectX::XMFLOAT3& vec);

				//**  division / ���Z  **//
				/// <summary>
				///	int�^�Ƃ̏��Z�p�I�y���[�^�[	</summary>
				/// <param name="i">
				///	int�l	</param>
				/// <returns>
				/// �l�̏��Z����	</returns>
				Vector3 operator/(int i);
				/// <summary>
				///	float�^�Ƃ̏��Z�p�I�y���[�^�[	</summary>
				/// <param name="f">
				///	float�l	</param>
				/// <returns>
				/// �l�̏��Z����	</returns>
				Vector3 operator/(float f);
				/// <summary>
				///	Vector3�^�Ƃ̏��Z�p�I�y���[�^�[	</summary>
				/// <param name="vec">
				///	Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̏��Z����	</returns>
				Vector3 operator/(const Vector3& vec);

				//**  div assignment / ���Z���  **//
				/// <summary>
				///	int�^�Ƃ̏��Z����p�I�y���[�^�[	</summary>
				/// <param name="i">
				/// int�l	</param>
				/// <returns>
				///	�l�̏��Z�������	</returns>
				Vector3 operator/=(int i);
				/// <summary>
				///	float�^�Ƃ̏��Z����p�I�y���[�^�[	</summary>
				/// <param name="f">
				/// float�l	</param>
				/// <returns>
				/// �l�̏��Z����p�I�y���[�^�[	</returns>
				Vector3 operator/=(float f);
				/// <summary>
				///	Vector3�^�Ƃ̏��Z����p�I�y���[�^�[	</summary>
				/// <param name="vec">
				/// Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �l�̏��Z�������	</returns>
				Vector3 operator/=(const Vector3& vec);

				//**  equal,not equal / ���l,�񓙒l  **//
				/// <summary>
				/// Vector3�^�Ƃ̓��l����p�I�y���[�^�[
				/// </summary>
				/// <param name="vec">
				/// Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// ���l�Ȃ�true�A�񓙒l�Ȃ�false	</returns>
				bool operator==(const Vector3& vec);
				/// <summary>
				///	Vector3�^�Ƃ̔񓙒l����p�I�y���[�^�[	</summary>
				/// <param name="vec">
				/// Vector3�^�I�u�W�F�N�g	</param>
				/// <returns>
				/// �񓙒l�Ȃ�true�A���l�Ȃ�false	</returns>
				bool operator!=(const Vector3& vec);


				// ----- �L���X�g���Z�q ----- //
				/// <summary>
				///	XMFLOAT3�ւ̃L���X�g�p�I�y���[�^�[	</summary>
				operator DirectX::XMFLOAT3() const;
		};
	}
}