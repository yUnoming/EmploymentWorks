#pragma once
/**
* @file		Vector2.h
* @brief	Vector2�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "Vector3.h"
#include <d3d11.h>


namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// �Q�����̃x�N�g����\���N���X	</summary>
		class Vector2
		{
		public:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			///	x���W	</summary>
			float x = 0.0f;
			/// <summary>
			///	y���W	</summary>
			float y = 0.0f;

			// ----- functions / �֐� ----- //
			/// <summary>
			///	�R���X�g���N�^	</summary>
			Vector2() {};
			/// <summary>
			///	�����t���R���X�g���N�^	</summary>
			/// <param name="x">
			///	x���W�l	</param>
			/// <param name="y">
			/// y���W�l	</param>
			Vector2(float x, float y) : x(x), y(y) {};
			/// <summary>
			///	�����t���R���X�g���N�^	</summary>
			/// <param name="point">
			///	POINT�^�̒l	</param>
			Vector2(POINT point) : x(static_cast<float>(point.x)), y(static_cast<float>(point.y)) {};
			/// <summary>
			///	�f�X�g���N�^	</summary>
			virtual ~Vector2() {};

			// ���Z�q�̃I�[�o�[���[�h�Q
			//**  assignment / ���  **//
			/// <summary>
			///	Vector2�^�Ƃ̑���p�I�y���[�^�[	</summary>
			/// <param name="vec">
			///	Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �l�̑������	</returns>
			Vector2 operator=(const Vector2& vec);

			//**  addition / ���Z  **//
			/// <summary>
			/// int�^�Ƃ̉��Z�p�I�y���[�^�[
			/// </summary>
			/// <param name="i">
			/// int�l	</param>
			/// <returns>
			///	�l�̉��Z����	</returns>
			Vector2 operator+(int i);
			/// <summary>
			///	float�^�Ƃ̉��Z�p�I�y���[�^�[	</summary>
			/// <param name="f">
			///	float�l	</param>
			/// <returns>
			///	�l�̉��Z����	</returns>
			Vector2 operator+(float f);
			/// <summary>
			///	Vector2�^�Ƃ̉��Z�p�I�y���[�^�[	</summary>
			/// <param name="vec">
			/// Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �l�̉��Z����	</returns>
			Vector2 operator+(const Vector2& vec);

			//**  add assignment / ���Z���  **//
			/// <summary>
			///	int�^�Ƃ̉��Z����p�I�y���[�^�[		</summary>
			/// <param name="i">
			/// int�l	</param>
			/// <returns>
			/// �l�̉��Z�������	</returns>
			Vector2 operator+=(int i);
			/// <summary>
			///	float�^�Ƃ̉��Z����p�I�y���[�^�[	</summary>
			/// <param name="f">
			///	float�l	</param>
			/// <returns>
			/// �l�̉��Z�������	</returns>
			Vector2 operator+=(float f);
			/// <summary>
			///	Vector2�^�Ƃ̉��Z����p�I�y���[�^�[	</summary>
			/// <param name="vec">
			///	Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			///	�l�̉��Z�������	</returns>
			Vector2 operator+=(const Vector2& vec);

			//**  subtraction / ���Z  **//
			/// <summary>
			///	int�^�Ƃ̌��Z�p�I�y���[�^�[	</summary>
			/// <param name="i">
			/// int�l	</param>
			/// <returns>
			///	�l�̌��Z����	</returns>
			Vector2 operator-(int i);
			/// <summary>
			///	float�^�Ƃ̌��Z�p�I�y���[�^�[	</summary>
			/// <param name="f">
			///	float�l	</param>
			/// <returns>
			///	�l�̌��Z����	</returns>
			Vector2 operator-(float f);
			/// <summary>
			/// Vector2�^�Ƃ̌��Z�p�I�y���[�^�[
			/// </summary>
			/// <param name="vec">
			///	Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �l�̌��Z����	</returns>
			Vector2 operator-(const Vector2& vec);

			//**  sub assignment / ���Z���  **//
			/// <summary>
			///	int�^�Ƃ̌��Z����p�I�y���[�^�[		</summary>
			/// <param name="i">
			///	int�l	</param>
			/// <returns>
			/// �l�̌��Z�������	</returns>
			Vector2 operator-=(int i);
			/// <summary>
			/// float�^�Ƃ̌��Z����p�I�y���[�^�[
			/// </summary>
			/// <param name="f">
			/// float�l	</param>
			/// <returns>
			/// �l�̌��Z�������	</returns>
			Vector2 operator-=(float f);
			/// <summary>
			///	Vector2�^�Ƃ̌��Z����p�I�y���[�^�[	</summary>
			/// <param name="vec">
			///	Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �l�̌��Z�������	</returns>
			Vector2 operator-=(const Vector2& vec);

			//** multiplication / ��Z  **//
			/// <summary>
			///	int�^�Ƃ̏�Z�p�I�y���[�^�[	</summary>
			/// <param name="i">
			///	int�l	</param>
			/// <returns>
			/// �l�̏�Z����	</returns>
			Vector2 operator*(int i);
			/// <summary>
			///	float�^�Ƃ̏�Z�p�I�y���[�^�[	</summary>
			/// <param name="f">
			/// float�l	</param>
			/// <returns>
			/// �l�̏�Z����	</returns>
			Vector2 operator*(float f);
			/// <summary>
			/// Vector2�^�Ƃ̏�Z�p�I�y���[�^�[	</summary>
			/// <param name="vec">
			///	Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			///	�l�̏�Z����	</returns>
			Vector2 operator*(const Vector2& vec);

			//**  multi assignment / ��Z���  **//
			/// <summary>
			///	int�^�̏�Z����p�I�y���[�^�[	</summary>
			/// <param name="i">
			/// int�l	</param>
			/// <returns>
			/// �l�̏�Z�������	</returns>
			Vector2 operator*=(int i);
			/// <summary>
			///	float�^�Ƃ̏�Z����p�I�y���[�^�[	</summary>
			/// <param name="f">
			///	float�l	</param>
			/// <returns>
			/// �l�̏�Z�������	</returns>
			Vector2 operator*=(float f);
			/// <summary>
			/// Vector2�^�Ƃ̏�Z����p�I�y���[�^�[		</summary>
			/// <param name="vec">
			///	Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �l�̏�Z�������	</returns>
			Vector2 operator*=(const Vector2& vec);

			//**  division / ���Z  **//
			/// <summary>
			///	int�^�Ƃ̏��Z�p�I�y���[�^�[	</summary>
			/// <param name="i">
			///	int�l	</param>
			/// <returns>
			/// �l�̏��Z����	</returns>
			Vector2 operator/(int i);
			/// <summary>
			///	float�^�Ƃ̏��Z�p�I�y���[�^�[	</summary>
			/// <param name="f">
			///	float�l	</param>
			/// <returns>
			/// �l�̏��Z����	</returns>
			Vector2 operator/(float f);
			/// <summary>
			///	Vector2�^�Ƃ̏��Z�p�I�y���[�^�[	</summary>
			/// <param name="vec">
			///	Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �l�̏��Z����	</returns>
			Vector2 operator/(const Vector2& vec);

			//**  div assignment / ���Z���  **//
			/// <summary>
			///	int�^�Ƃ̏��Z����p�I�y���[�^�[	</summary>
			/// <param name="i">
			/// int�l	</param>
			/// <returns>
			///	�l�̏��Z�������	</returns>
			Vector2 operator/=(int i);
			/// <summary>
			///	float�^�Ƃ̏��Z����p�I�y���[�^�[	</summary>
			/// <param name="f">
			/// float�l	</param>
			/// <returns>
			/// �l�̏��Z����p�I�y���[�^�[	</returns>
			Vector2 operator/=(float f);
			/// <summary>
			///	Vector2�^�Ƃ̏��Z����p�I�y���[�^�[	</summary>
			/// <param name="vec">
			/// Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �l�̏��Z�������	</returns>
			Vector2 operator/=(const Vector2& vec);

			//**  equal,not equal / ���l,�񓙒l  **//
			/// <summary>
			/// Vector2�^�Ƃ̓��l����p�I�y���[�^�[
			/// </summary>
			/// <param name="vec">
			/// Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// ���l�Ȃ�true�A�񓙒l�Ȃ�false	</returns>
			bool operator==(const Vector2& vec);
			/// <summary>
			///	Vector2�^�Ƃ̔񓙒l����p�I�y���[�^�[	</summary>
			/// <param name="vec">
			/// Vector2�^�I�u�W�F�N�g	</param>
			/// <returns>
			/// �񓙒l�Ȃ�true�A���l�Ȃ�false	</returns>
			bool operator!=(const Vector2& vec);

			// ----- �L���X�g���Z�q ----- //
			/// <summary>
			///	Vector3�ւ̃L���X�g�p�I�y���[�^�[	</summary>
			operator Vector3() const;
			/// <summary>
			///	POINT�^�ւ̃L���X�g�p�I�y���[�^�[	</summary>
			operator tagPOINT() const;
		};
	}
}