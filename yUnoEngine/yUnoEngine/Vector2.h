#pragma once

namespace PublicSystem
{
	class Vector2
	{
		public:
			// ----- variables / �ϐ� ----- //
			float x = 0.0f;
			float y = 0.0f;

			// ----- methods / �֐� ----- //
			Vector2() {};
			Vector2(float _x, float _y) : x(_x), y(_y){};
			virtual ~Vector2() {};

			// ���Z�q�̃I�[�o�[���[�h�Q
			//**  addition / ���Z  **//
			Vector2 operator+(int _i);
			Vector2 operator+(float _f);
			Vector2 operator+(const Vector2& _vec);

			//**  add assignment / ���Z���  **//
			Vector2 operator+=(int _i);
			Vector2 operator+=(float _f);
			Vector2 operator+=(const Vector2& _vec);

			//**  subtraction / ���Z  **//
			Vector2 operator-(int _i);
			Vector2 operator-(float _f);
			Vector2 operator-(const Vector2& _vec);

			//**  sub assignment / ���Z���  **//
			Vector2 operator-=(int _i);
			Vector2 operator-=(float _f);
			Vector2 operator-=(const Vector2& _vec);

			//** multiplication / ��Z  **//
			Vector2 operator*(int _i);
			Vector2 operator*(float _f);
			Vector2 operator*(const Vector2& _vec);

			//**  multi assignment / ��Z���  **//
			Vector2 operator*=(int _i);
			Vector2 operator*=(float _f);
			Vector2 operator*=(const Vector2& _vec);

			//**  division / ���Z  **//
			Vector2 operator/(int _i);
			Vector2 operator/(float _f);
			Vector2 operator/(const Vector2& _vec);

			//**  div assignment / ���Z���  **//
			Vector2 operator/=(int _i);
			Vector2 operator/=(float _f);
			Vector2 operator/=(const Vector2& _vec);

			//**  equal,not equal / ���l,�񓙒l  **//
			bool operator==(const Vector2& _vec);
			bool operator!=(const Vector2& _vec);
	};
}

