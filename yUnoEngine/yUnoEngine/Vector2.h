#pragma once

namespace PublicSystem
{
	/// <summary>
	/// XY˝ĘĚŔWlđľ¤˝ßĚNX
	/// </summary>
	class Vector2
	{
		public:
			// ----- variables / Ď ----- //
			float x = 0.0f;
			float y = 0.0f;

			// ----- functions / Ö ----- //
			Vector2() {};
			Vector2(float _x, float _y) : x(_x), y(_y){};
			virtual ~Vector2() {};

			// ZqĚI[o[[hQ
			//**  addition / ÁZ  **//
			Vector2 operator+(int _i);
			Vector2 operator+(float _f);
			Vector2 operator+(const Vector2& _vec);

			//**  add assignment / ÁZăü  **//
			Vector2 operator+=(int _i);
			Vector2 operator+=(float _f);
			Vector2 operator+=(const Vector2& _vec);

			//**  subtraction / ¸Z  **//
			Vector2 operator-(int _i);
			Vector2 operator-(float _f);
			Vector2 operator-(const Vector2& _vec);

			//**  sub assignment / ¸Zăü  **//
			Vector2 operator-=(int _i);
			Vector2 operator-=(float _f);
			Vector2 operator-=(const Vector2& _vec);

			//** multiplication / ćZ  **//
			Vector2 operator*(int _i);
			Vector2 operator*(float _f);
			Vector2 operator*(const Vector2& _vec);

			//**  multi assignment / ćZăü  **//
			Vector2 operator*=(int _i);
			Vector2 operator*=(float _f);
			Vector2 operator*=(const Vector2& _vec);

			//**  division / Z  **//
			Vector2 operator/(int _i);
			Vector2 operator/(float _f);
			Vector2 operator/(const Vector2& _vec);

			//**  div assignment / Zăü  **//
			Vector2 operator/=(int _i);
			Vector2 operator/=(float _f);
			Vector2 operator/=(const Vector2& _vec);

			//**  equal,not equal / l,ńl  **//
			bool operator==(const Vector2& _vec);
			bool operator!=(const Vector2& _vec);
	};
}

