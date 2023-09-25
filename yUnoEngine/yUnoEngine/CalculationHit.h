#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector3.h"
#include "Transform.h"

namespace PublicSystem
{
	/// <summary>
	/// 対象と対象が当たっているかどうかを計算する機能が備わったクラス
	/// </summary>
	class CalculationHit
	{
		public:
			// ----- functions / 関数 ----- //
			// **  主が線分の当たり判定  ** //
			/// <summary>
			/// 線分と線分が当たっているかを計算する
			/// </summary>
			/// <param name = "引数１：_mySegment_Start">
			/// ／自身として扱う線分の始点
			/// </param>
			/// <param name = "引数２：_mySegment_End">
			/// ／自身として扱う線分の終点
			/// </param>
			/// <param name = "引数３：_otherSegment_End">
			/// ／相手として扱う線分の始点
			/// </param>
			/// <param name = "引数４：_otherSegment_End">
			/// ／相手として扱う線分の終点
			/// </param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す
			/// </returns>
			static bool SegmentToSegment(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherSegment_Start, Vector3 _otherSegment_End);
			/// <summary>
			/// 線分と四角形が当たっているかを計算する
			/// </summary>
			/// <param name = "引数１：_mySegment_Start">
			/// ／自身として扱う線分の始点
			/// </param>
			/// <param name = "引数２：_mySegment_End">
			/// ／自身として扱う線分の終点
			/// </param>
			/// <param name = "引数３：_otherRightTop">
			/// ／相手として扱う四角形の右上頂点
			/// </param>
			/// <param name = "引数４：_otherLeftBottom">
			/// ／相手として扱う線分の左下頂点
			/// </param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す
			/// </returns>
			static bool SegmentToQuadrangle(Vector3 _mySegment_Start, Vector3 _mySegment_End, Vector3 _otherRightTop, Vector3 _otherLeftBottom);
			/// <summary>
			/// 線分と六面体が当たっているかを計算する
			/// </summary>
			/// <param name = "引数１：_mySegment_Start">
			/// ／自身として扱う線分の始点
			/// </param>
			/// <param name = "引数２：_mySegment_End">
			/// ／自身として扱う線分の終点
			/// </param>
			/// <param name = "引数３：_otherHexahedron">
			/// ／相手として扱う六面体のTransform情報
			/// </param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す
			/// </returns>
			static bool SegmentToHexahedron(Vector3 _mySegment_Start, Vector3 _mySegment_End, const Transform* _otherHexahedron);

			// **  主が点の当たり判定  ** //
			/// <summary>
			/// 点と四角形が当たっているかを計算する
			/// </summary>
			/// <param name = "引数１：_myPoint">
			/// ／自身として扱う点の座標値
			/// </param>
			/// <param name = "引数３：_otherRightTop">
			/// ／相手として扱う四角形の右上頂点
			/// </param>
			/// <param name = "引数４：_otherLeftBottom">
			/// ／相手として扱う線分の左下頂点
			/// </param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す
			/// </returns>
			static bool PointToQuadrangle(Vector3 _myPoint, Vector3 _otherRightTop, Vector3 _otherLeftBottom);
	};
}

