#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <DirectXMath.h>


namespace PublicSystem
{
	// ３次元のベクトルを表すクラス
	class Vector3
	{
		public:
			// ----- variables / 変数 ----- //
			float x = 1.0f;
			float y = 1.0f;
			float z = 1.0f;


			// ----- functions / 関数 ----- //
			Vector3() {};
			Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
			Vector3(float _x, float _y) : x(_x), y(_y) {};
			virtual ~Vector3() {};


			// ----- 演算子のオーバーロード群 ----- //
			//**  assignment / 代入  **//
			Vector3 operator=(const Vector3& _vec);

			//**  addition / 加算  **//
			Vector3 operator+(int _i);
			Vector3 operator+(float _f);
			Vector3 operator+(const Vector3 &_vec);

			//**  add assignment / 加算代入  **//
			Vector3 operator+=(int _i);
			Vector3 operator+=(float _f);
			Vector3 operator+=(const Vector3 &_vec);

			//**  subtraction / 減算  **//
			Vector3 operator-(int _i);
			Vector3 operator-(float _f);
			Vector3 operator-(const Vector3 &_vec);

			//**  sub assignment / 減算代入  **//
			Vector3 operator-=(int _i);
			Vector3 operator-=(float _f);
			Vector3 operator-=(const Vector3& _vec);

			//** multiplication / 乗算  **//
			Vector3 operator*(int _i);
			Vector3 operator*(float _f);
			Vector3 operator*(const Vector3 &_vec);

			//**  multi assignment / 乗算代入  **//
			Vector3 operator*=(int _i);
			Vector3 operator*=(float _f);
			Vector3 operator*=(const Vector3& _vec);

			//**  division / 除算  **//
			Vector3 operator/(int _i);
			Vector3 operator/(float _f);
			Vector3 operator/(const Vector3 &_vec);

			//**  div assignment / 除算代入  **//
			Vector3 operator/=(int _i);
			Vector3 operator/=(float _f);
			Vector3 operator/=(const Vector3& _vec);

			//**  equal,not equal / 等値,非等値  **//
			bool operator==(const Vector3& _vec);
			bool operator!=(const Vector3& _vec);


			// ----- キャスト演算子 ----- //
			operator DirectX::XMFLOAT3() const;
	};
}

