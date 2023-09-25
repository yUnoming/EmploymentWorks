#pragma once

namespace PublicSystem
{
	class Vector3
	{
		public:
			// ----- variables / •Ï” ----- //
			float x = 1.0f;
			float y = 1.0f;
			float z = 1.0f;

			// ----- functions / ŠÖ” ----- //
			Vector3() {};
			Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
			Vector3(float _x, float _y) : x(_x), y(_y) {};
			virtual ~Vector3() {};

			// ‰‰Zq‚ÌƒI[ƒo[ƒ[ƒhŒQ
			//**  assignment / ‘ã“ü  **//
			Vector3 operator=(const Vector3& _vec);

			//**  addition / ‰ÁZ  **//
			Vector3 operator+(int _i);
			Vector3 operator+(float _f);
			Vector3 operator+(const Vector3 &_vec);

			//**  add assignment / ‰ÁZ‘ã“ü  **//
			Vector3 operator+=(int _i);
			Vector3 operator+=(float _f);
			Vector3 operator+=(const Vector3 &_vec);

			//**  subtraction / Œ¸Z  **//
			Vector3 operator-(int _i);
			Vector3 operator-(float _f);
			Vector3 operator-(const Vector3 &_vec);

			//**  sub assignment / Œ¸Z‘ã“ü  **//
			Vector3 operator-=(int _i);
			Vector3 operator-=(float _f);
			Vector3 operator-=(const Vector3& _vec);

			//** multiplication / æZ  **//
			Vector3 operator*(int _i);
			Vector3 operator*(float _f);
			Vector3 operator*(const Vector3 &_vec);

			//**  multi assignment / æZ‘ã“ü  **//
			Vector3 operator*=(int _i);
			Vector3 operator*=(float _f);
			Vector3 operator*=(const Vector3& _vec);

			//**  division / œZ  **//
			Vector3 operator/(int _i);
			Vector3 operator/(float _f);
			Vector3 operator/(const Vector3 &_vec);

			//**  div assignment / œZ‘ã“ü  **//
			Vector3 operator/=(int _i);
			Vector3 operator/=(float _f);
			Vector3 operator/=(const Vector3& _vec);

			//**  equal,not equal / “™’l,”ñ“™’l  **//
			bool operator==(const Vector3& _vec);
			bool operator!=(const Vector3& _vec);
	};
}

