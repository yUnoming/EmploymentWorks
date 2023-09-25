#pragma once

namespace PublicSystem
{
	class Vector3
	{
		public:
			// ----- variables / �ϐ� ----- //
			float x = 1.0f;
			float y = 1.0f;
			float z = 1.0f;

			// ----- functions / �֐� ----- //
			Vector3() {};
			Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
			Vector3(float _x, float _y) : x(_x), y(_y) {};
			virtual ~Vector3() {};

			// ���Z�q�̃I�[�o�[���[�h�Q
			//**  assignment / ���  **//
			Vector3 operator=(const Vector3& _vec);

			//**  addition / ���Z  **//
			Vector3 operator+(int _i);
			Vector3 operator+(float _f);
			Vector3 operator+(const Vector3 &_vec);

			//**  add assignment / ���Z���  **//
			Vector3 operator+=(int _i);
			Vector3 operator+=(float _f);
			Vector3 operator+=(const Vector3 &_vec);

			//**  subtraction / ���Z  **//
			Vector3 operator-(int _i);
			Vector3 operator-(float _f);
			Vector3 operator-(const Vector3 &_vec);

			//**  sub assignment / ���Z���  **//
			Vector3 operator-=(int _i);
			Vector3 operator-=(float _f);
			Vector3 operator-=(const Vector3& _vec);

			//** multiplication / ��Z  **//
			Vector3 operator*(int _i);
			Vector3 operator*(float _f);
			Vector3 operator*(const Vector3 &_vec);

			//**  multi assignment / ��Z���  **//
			Vector3 operator*=(int _i);
			Vector3 operator*=(float _f);
			Vector3 operator*=(const Vector3& _vec);

			//**  division / ���Z  **//
			Vector3 operator/(int _i);
			Vector3 operator/(float _f);
			Vector3 operator/(const Vector3 &_vec);

			//**  div assignment / ���Z���  **//
			Vector3 operator/=(int _i);
			Vector3 operator/=(float _f);
			Vector3 operator/=(const Vector3& _vec);

			//**  equal,not equal / ���l,�񓙒l  **//
			bool operator==(const Vector3& _vec);
			bool operator!=(const Vector3& _vec);
	};
}

