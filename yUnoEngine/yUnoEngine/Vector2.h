#pragma once

namespace PublicSystem
{
	/// <summary>
	/// XY•½–Ê‚ÌÀ•W’l‚ğˆµ‚¤‚½‚ß‚ÌƒNƒ‰ƒX
	/// </summary>
	class Vector2
	{
		public:
			// ----- variables / •Ï” ----- //
			float x = 0.0f;
			float y = 0.0f;

			// ----- functions / ŠÖ” ----- //
			Vector2() {};
			Vector2(float _x, float _y) : x(_x), y(_y){};
			virtual ~Vector2() {};

			// ‰‰Zq‚ÌƒI[ƒo[ƒ[ƒhŒQ
			//**  addition / ‰ÁZ  **//
			Vector2 operator+(int _i);
			Vector2 operator+(float _f);
			Vector2 operator+(const Vector2& _vec);

			//**  add assignment / ‰ÁZ‘ã“ü  **//
			Vector2 operator+=(int _i);
			Vector2 operator+=(float _f);
			Vector2 operator+=(const Vector2& _vec);

			//**  subtraction / Œ¸Z  **//
			Vector2 operator-(int _i);
			Vector2 operator-(float _f);
			Vector2 operator-(const Vector2& _vec);

			//**  sub assignment / Œ¸Z‘ã“ü  **//
			Vector2 operator-=(int _i);
			Vector2 operator-=(float _f);
			Vector2 operator-=(const Vector2& _vec);

			//** multiplication / æZ  **//
			Vector2 operator*(int _i);
			Vector2 operator*(float _f);
			Vector2 operator*(const Vector2& _vec);

			//**  multi assignment / æZ‘ã“ü  **//
			Vector2 operator*=(int _i);
			Vector2 operator*=(float _f);
			Vector2 operator*=(const Vector2& _vec);

			//**  division / œZ  **//
			Vector2 operator/(int _i);
			Vector2 operator/(float _f);
			Vector2 operator/(const Vector2& _vec);

			//**  div assignment / œZ‘ã“ü  **//
			Vector2 operator/=(int _i);
			Vector2 operator/=(float _f);
			Vector2 operator/=(const Vector2& _vec);

			//**  equal,not equal / “™’l,”ñ“™’l  **//
			bool operator==(const Vector2& _vec);
			bool operator!=(const Vector2& _vec);
	};
}

