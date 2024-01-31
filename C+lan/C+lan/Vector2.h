#pragma once
/**
* @file		Vector2.h
* @brief	Vector2クラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector3.h"
#include <d3d11.h>


namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		/// ２次元のベクトルを表すクラス	</summary>
		class Vector2
		{
		public:
			// ----- variables / 変数 ----- //
			/// <summary>
			///	x座標	</summary>
			float x = 0.0f;
			/// <summary>
			///	y座標	</summary>
			float y = 0.0f;

			// ----- functions / 関数 ----- //
			/// <summary>
			///	コンストラクタ	</summary>
			Vector2() {};
			/// <summary>
			///	引数付きコンストラクタ	</summary>
			/// <param name="x">
			///	x座標値	</param>
			/// <param name="y">
			/// y座標値	</param>
			Vector2(float x, float y) : x(x), y(y) {};
			/// <summary>
			///	引数付きコンストラクタ	</summary>
			/// <param name="point">
			///	POINT型の値	</param>
			Vector2(POINT point) : x(static_cast<float>(point.x)), y(static_cast<float>(point.y)) {};
			/// <summary>
			///	デストラクタ	</summary>
			virtual ~Vector2() {};

			// 演算子のオーバーロード群
			//**  assignment / 代入  **//
			/// <summary>
			///	Vector2型との代入用オペレーター	</summary>
			/// <param name="vec">
			///	Vector2型オブジェクト	</param>
			/// <returns>
			/// 値の代入結果	</returns>
			Vector2 operator=(const Vector2& vec);

			//**  addition / 加算  **//
			/// <summary>
			/// int型との加算用オペレーター
			/// </summary>
			/// <param name="i">
			/// int値	</param>
			/// <returns>
			///	値の加算結果	</returns>
			Vector2 operator+(int i);
			/// <summary>
			///	float型との加算用オペレーター	</summary>
			/// <param name="f">
			///	float値	</param>
			/// <returns>
			///	値の加算結果	</returns>
			Vector2 operator+(float f);
			/// <summary>
			///	Vector2型との加算用オペレーター	</summary>
			/// <param name="vec">
			/// Vector2型オブジェクト	</param>
			/// <returns>
			/// 値の加算結果	</returns>
			Vector2 operator+(const Vector2& vec);

			//**  add assignment / 加算代入  **//
			/// <summary>
			///	int型との加算代入用オペレーター		</summary>
			/// <param name="i">
			/// int値	</param>
			/// <returns>
			/// 値の加算代入結果	</returns>
			Vector2 operator+=(int i);
			/// <summary>
			///	float型との加算代入用オペレーター	</summary>
			/// <param name="f">
			///	float値	</param>
			/// <returns>
			/// 値の加算代入結果	</returns>
			Vector2 operator+=(float f);
			/// <summary>
			///	Vector2型との加算代入用オペレーター	</summary>
			/// <param name="vec">
			///	Vector2型オブジェクト	</param>
			/// <returns>
			///	値の加算代入結果	</returns>
			Vector2 operator+=(const Vector2& vec);

			//**  subtraction / 減算  **//
			/// <summary>
			///	int型との減算用オペレーター	</summary>
			/// <param name="i">
			/// int値	</param>
			/// <returns>
			///	値の減算結果	</returns>
			Vector2 operator-(int i);
			/// <summary>
			///	float型との減算用オペレーター	</summary>
			/// <param name="f">
			///	float値	</param>
			/// <returns>
			///	値の減算結果	</returns>
			Vector2 operator-(float f);
			/// <summary>
			/// Vector2型との減算用オペレーター
			/// </summary>
			/// <param name="vec">
			///	Vector2型オブジェクト	</param>
			/// <returns>
			/// 値の減算結果	</returns>
			Vector2 operator-(const Vector2& vec);

			//**  sub assignment / 減算代入  **//
			/// <summary>
			///	int型との減算代入用オペレーター		</summary>
			/// <param name="i">
			///	int値	</param>
			/// <returns>
			/// 値の減算代入結果	</returns>
			Vector2 operator-=(int i);
			/// <summary>
			/// float型との減算代入用オペレーター
			/// </summary>
			/// <param name="f">
			/// float値	</param>
			/// <returns>
			/// 値の減算代入結果	</returns>
			Vector2 operator-=(float f);
			/// <summary>
			///	Vector2型との減算代入用オペレーター	</summary>
			/// <param name="vec">
			///	Vector2型オブジェクト	</param>
			/// <returns>
			/// 値の減算代入結果	</returns>
			Vector2 operator-=(const Vector2& vec);

			//** multiplication / 乗算  **//
			/// <summary>
			///	int型との乗算用オペレーター	</summary>
			/// <param name="i">
			///	int値	</param>
			/// <returns>
			/// 値の乗算結果	</returns>
			Vector2 operator*(int i);
			/// <summary>
			///	float型との乗算用オペレーター	</summary>
			/// <param name="f">
			/// float値	</param>
			/// <returns>
			/// 値の乗算結果	</returns>
			Vector2 operator*(float f);
			/// <summary>
			/// Vector2型との乗算用オペレーター	</summary>
			/// <param name="vec">
			///	Vector2型オブジェクト	</param>
			/// <returns>
			///	値の乗算結果	</returns>
			Vector2 operator*(const Vector2& vec);

			//**  multi assignment / 乗算代入  **//
			/// <summary>
			///	int型の乗算代入用オペレーター	</summary>
			/// <param name="i">
			/// int値	</param>
			/// <returns>
			/// 値の乗算代入結果	</returns>
			Vector2 operator*=(int i);
			/// <summary>
			///	float型との乗算代入用オペレーター	</summary>
			/// <param name="f">
			///	float値	</param>
			/// <returns>
			/// 値の乗算代入結果	</returns>
			Vector2 operator*=(float f);
			/// <summary>
			/// Vector2型との乗算代入用オペレーター		</summary>
			/// <param name="vec">
			///	Vector2型オブジェクト	</param>
			/// <returns>
			/// 値の乗算代入結果	</returns>
			Vector2 operator*=(const Vector2& vec);

			//**  division / 除算  **//
			/// <summary>
			///	int型との除算用オペレーター	</summary>
			/// <param name="i">
			///	int値	</param>
			/// <returns>
			/// 値の除算結果	</returns>
			Vector2 operator/(int i);
			/// <summary>
			///	float型との除算用オペレーター	</summary>
			/// <param name="f">
			///	float値	</param>
			/// <returns>
			/// 値の除算結果	</returns>
			Vector2 operator/(float f);
			/// <summary>
			///	Vector2型との除算用オペレーター	</summary>
			/// <param name="vec">
			///	Vector2型オブジェクト	</param>
			/// <returns>
			/// 値の除算結果	</returns>
			Vector2 operator/(const Vector2& vec);

			//**  div assignment / 除算代入  **//
			/// <summary>
			///	int型との除算代入用オペレーター	</summary>
			/// <param name="i">
			/// int値	</param>
			/// <returns>
			///	値の除算代入結果	</returns>
			Vector2 operator/=(int i);
			/// <summary>
			///	float型との除算代入用オペレーター	</summary>
			/// <param name="f">
			/// float値	</param>
			/// <returns>
			/// 値の除算代入用オペレーター	</returns>
			Vector2 operator/=(float f);
			/// <summary>
			///	Vector2型との除算代入用オペレーター	</summary>
			/// <param name="vec">
			/// Vector2型オブジェクト	</param>
			/// <returns>
			/// 値の除算代入結果	</returns>
			Vector2 operator/=(const Vector2& vec);

			//**  equal,not equal / 等値,非等値  **//
			/// <summary>
			/// Vector2型との等値判定用オペレーター
			/// </summary>
			/// <param name="vec">
			/// Vector2型オブジェクト	</param>
			/// <returns>
			/// 等値ならtrue、非等値ならfalse	</returns>
			bool operator==(const Vector2& vec);
			/// <summary>
			///	Vector2型との非等値判定用オペレーター	</summary>
			/// <param name="vec">
			/// Vector2型オブジェクト	</param>
			/// <returns>
			/// 非等値ならtrue、等値ならfalse	</returns>
			bool operator!=(const Vector2& vec);

			// ----- キャスト演算子 ----- //
			/// <summary>
			///	Vector3へのキャスト用オペレーター	</summary>
			operator Vector3() const;
			/// <summary>
			///	POINT型へのキャスト用オペレーター	</summary>
			operator tagPOINT() const;
		};
	}
}