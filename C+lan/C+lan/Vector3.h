#pragma once
/**
* @file		Vector3.h
* @brief	Vector3クラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.06
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <DirectXMath.h>

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	３次元のベクトルを表すクラス	</summary>
		class Vector3
		{
			public:
				// ----- variables / 変数 ----- //
				/// <summary>
				///	x座標	</summary>
				float x = 1.0f;
				/// <summary>
				///	y座標	</summary>
				float y = 1.0f;
				/// <summary>
				///	z座標	</summary>
				float z = 1.0f;


				// ----- functions / 関数 ----- //
				/// <summary>
				///	コンストラクタ	</summary>
				Vector3() {};
				/// <summary>
				///	引数付きコンストラクタ	</summary>
				/// <param name="x">
				///	x座標値	</param>
				/// <param name="y">
				/// y座標値	</param>
				/// <param name="z">
				/// z座標値	</param>
				Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
				/// <summary>
				/// 引数付きコンストラクタ
				/// </summary>
				/// <param name="x">
				/// x座標値	</param>
				/// <param name="y">
				/// y座標値	</param>
				Vector3(float x, float y) : x(x), y(y) {};
				virtual ~Vector3() {};


				// ----- 演算子のオーバーロード群 ----- //
				//**  assignment / 代入  **//
				/// <summary>
				///	Vector3型との代入用オペレーター	</summary>
				/// <param name="vec">
				///	Vector3型オブジェクト	</param>
				/// <returns>
				/// 値の代入結果	</returns>
				Vector3 operator=(const Vector3& vec);
				/// <summary>
				///	DirectX::XMFLOAT3型との代入用オペレーター	</summary>
				/// <param name="vec">
				///	DirectX::XMFLOAT3型オブジェクト	</param>
				/// <returns>
				/// 値の代入結果	</returns>
				Vector3 operator=(const DirectX::XMFLOAT3& vec);

				//**  addition / 加算  **//
				/// <summary>
				///	int型との加算用オペレーター	</summary>
				/// <param name="i">
				/// int値	</param>
				/// <returns>
				///	値の加算結果	</returns>
				Vector3 operator+(int i);
				/// <summary>
			///	float型との加算用オペレーター	</summary>
			/// <param name="f">
			///	float値	</param>
			/// <returns>
			///	値の加算結果	</returns>
				Vector3 operator+(float f);
				/// <summary>
				///	Vector3型との加算用オペレーター	</summary>
				/// <param name="vec">
				/// Vector3型オブジェクト	</param>
				/// <returns>
				/// 値の加算結果	</returns>
				Vector3 operator+(const Vector3& vec);

				//**  add assignment / 加算代入  **//
				/// <summary>
				///	int型との加算代入用オペレーター		</summary>
				/// <param name="i">
				/// int値	</param>
				/// <returns>
				/// 値の加算代入結果	</returns>
				Vector3 operator+=(int i);
				/// <summary>
				///	float型との加算代入用オペレーター	</summary>
				/// <param name="f">
				///	float値	</param>
				/// <returns>
				/// 値の加算代入結果	</returns>
				Vector3 operator+=(float f);
				/// <summary>
				///	Vector3型との加算代入用オペレーター	</summary>
				/// <param name="vec">
				///	Vector3型オブジェクト	</param>
				/// <returns>
				///	値の加算代入結果	</returns>
				Vector3 operator+=(const Vector3& vec);
				/// <summary>
				///	DirectX::XMFLOAT3型との加算代入用オペレーター	</summary>
				/// <param name="vec">
				///	DirectX::XMFLOAT3型オブジェクト	</param>
				/// <returns>
				///	値の加算代入結果	</returns>
				Vector3 operator+=(const DirectX::XMFLOAT3& vec);

				//**  subtraction / 減算  **//
				/// <summary>
				///	int型との減算用オペレーター	</summary>
				/// <param name="i">
				/// int値	</param>
				/// <returns>
				///	値の減算結果	</returns>
				Vector3 operator-(int i);
				/// <summary>
				///	float型との減算用オペレーター	</summary>
				/// <param name="f">
				///	float値	</param>
				/// <returns>
				///	値の減算結果	</returns>
				Vector3 operator-(float f);
				/// <summary>
				/// Vector3型との減算用オペレーター
				/// </summary>
				/// <param name="vec">
				///	Vector3型オブジェクト	</param>
				/// <returns>
				/// 値の減算結果	</returns>
				Vector3 operator-(const Vector3& vec);

				//**  sub assignment / 減算代入  **//
				/// <summary>
				///	int型との減算代入用オペレーター		</summary>
				/// <param name="i">
				///	int値	</param>
				/// <returns>
				/// 値の減算代入結果	</returns>
				Vector3 operator-=(int i);
				/// <summary>
				/// float型との減算代入用オペレーター
				/// </summary>
				/// <param name="f">
				/// float値	</param>
				/// <returns>
				/// 値の減算代入結果	</returns>
				Vector3 operator-=(float f);
				/// <summary>
				///	Vector3型との減算代入用オペレーター	</summary>
				/// <param name="vec">
				///	Vector3型オブジェクト	</param>
				/// <returns>
				/// 値の減算代入結果	</returns>
				Vector3 operator-=(const Vector3& vec);

				//** multiplication / 乗算  **//
				/// <summary>
				///	int型との乗算用オペレーター	</summary>
				/// <param name="i">
				///	int値	</param>
				/// <returns>
				/// 値の乗算結果	</returns>
				Vector3 operator*(int i);
				/// <summary>
				///	float型との乗算用オペレーター	</summary>
				/// <param name="f">
				/// float値	</param>
				/// <returns>
				/// 値の乗算結果	</returns>
				Vector3 operator*(float f);
				/// <summary>
				/// Vector3型との乗算用オペレーター	</summary>
				/// <param name="vec">
				///	Vector3型オブジェクト	</param>
				/// <returns>
				///	値の乗算結果	</returns>
				Vector3 operator*(const Vector3& vec);

				//**  multi assignment / 乗算代入  **//
				/// <summary>
				///	int型の乗算代入用オペレーター	</summary>
				/// <param name="i">
				/// int値	</param>
				/// <returns>
				/// 値の乗算代入結果	</returns>
				Vector3 operator*=(int i);
				/// <summary>
				///	float型との乗算代入用オペレーター	</summary>
				/// <param name="f">
				///	float値	</param>
				/// <returns>
				/// 値の乗算代入結果	</returns>
				Vector3 operator*=(float f);
				/// <summary>
				/// Vector3型との乗算代入用オペレーター		</summary>
				/// <param name="vec">
				///	Vector3型オブジェクト	</param>
				/// <returns>
				/// 値の乗算代入結果	</returns>
				Vector3 operator*=(const Vector3& vec);
				/// <summary>
				/// DirectX::XMFLOAT3型との乗算代入用オペレーター		</summary>
				/// <param name="vec">
				///	DirectX::XMFLOAT3型オブジェクト	</param>
				/// <returns>
				/// 値の乗算代入結果	</returns>
				Vector3 operator*=(const DirectX::XMFLOAT3& vec);

				//**  division / 除算  **//
				/// <summary>
				///	int型との除算用オペレーター	</summary>
				/// <param name="i">
				///	int値	</param>
				/// <returns>
				/// 値の除算結果	</returns>
				Vector3 operator/(int i);
				/// <summary>
				///	float型との除算用オペレーター	</summary>
				/// <param name="f">
				///	float値	</param>
				/// <returns>
				/// 値の除算結果	</returns>
				Vector3 operator/(float f);
				/// <summary>
				///	Vector3型との除算用オペレーター	</summary>
				/// <param name="vec">
				///	Vector3型オブジェクト	</param>
				/// <returns>
				/// 値の除算結果	</returns>
				Vector3 operator/(const Vector3& vec);

				//**  div assignment / 除算代入  **//
				/// <summary>
				///	int型との除算代入用オペレーター	</summary>
				/// <param name="i">
				/// int値	</param>
				/// <returns>
				///	値の除算代入結果	</returns>
				Vector3 operator/=(int i);
				/// <summary>
				///	float型との除算代入用オペレーター	</summary>
				/// <param name="f">
				/// float値	</param>
				/// <returns>
				/// 値の除算代入用オペレーター	</returns>
				Vector3 operator/=(float f);
				/// <summary>
				///	Vector3型との除算代入用オペレーター	</summary>
				/// <param name="vec">
				/// Vector3型オブジェクト	</param>
				/// <returns>
				/// 値の除算代入結果	</returns>
				Vector3 operator/=(const Vector3& vec);

				//**  equal,not equal / 等値,非等値  **//
				/// <summary>
				/// Vector3型との等値判定用オペレーター
				/// </summary>
				/// <param name="vec">
				/// Vector3型オブジェクト	</param>
				/// <returns>
				/// 等値ならtrue、非等値ならfalse	</returns>
				bool operator==(const Vector3& vec);
				/// <summary>
				///	Vector3型との非等値判定用オペレーター	</summary>
				/// <param name="vec">
				/// Vector3型オブジェクト	</param>
				/// <returns>
				/// 非等値ならtrue、等値ならfalse	</returns>
				bool operator!=(const Vector3& vec);


				// ----- キャスト演算子 ----- //
				/// <summary>
				///	XMFLOAT3へのキャスト用オペレーター	</summary>
				operator DirectX::XMFLOAT3() const;
		};
	}
}