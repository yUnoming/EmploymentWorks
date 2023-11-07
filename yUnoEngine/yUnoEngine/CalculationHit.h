#pragma once
/**
* @file		CalculationHit.h
* @brief	CalculationHitクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.02
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　   ファイルのインクルード        //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "Vector3.h"
#include "Transform.h"

namespace PublicSystem
{
	/// <summary>
	/// 対象と対象が当たっているかどうかを計算する機能が備わったクラス	</summary>
	class CalculationHit
	{
		public:
			// ----- functions / 関数 ----- //
			// **  自身が線分の当たり判定  ** //
			/// <summary>
			/// 線分と線分が当たっているかを計算する	</summary>
			/// <param name = "mySegmentStart">
			/// 自身として扱う線分の始点	</param>
			/// <param name = "mySegmentEnd">
			/// 自身として扱う線分の終点	</param>
			/// <param name = "otherSegmentEnd">
			/// 相手として扱う線分の始点	</param>
			/// <param name = "otherSegmentEnd">
			/// 相手として扱う線分の終点	</param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す	</returns>
			static bool SegmentToSegment(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 otherSegmentStart, Vector3 otherSegmentEnd);
			/// <summary>
			/// 線分と四角形が当たっているかを計算する
			/// </summary>
			/// <param name = "mySegmentStart">
			/// 自身として扱う線分の始点	</param>
			/// <param name = "mySegmentEnd">
			/// 自身として扱う線分の終点	</param>
			/// <param name = "otherRightTop">
			/// 相手として扱う四角形の右上頂点	</param>
			/// <param name = "otherLeftBottom">
			/// 相手として扱う線分の左下頂点	</param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す	</returns>
			static bool SegmentToQuadrangle(Vector3 mySegmentStart, Vector3 mySegmentEnd, Vector3 otherRightTop, Vector3 otherLeftBottom);
			/// <summary>
			/// 線分と六面体が当たっているかを計算する	</summary>
			/// <param name = "mySegmentStart">
			/// 自身として扱う線分の始点	</param>
			/// <param name = "mySegmentEnd">
			/// 自身として扱う線分の終点	</param>
			/// <param name = "otherHexahedron">
			/// 相手として扱う六面体のTransform情報	</param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す	</returns>
			static bool SegmentToHexahedron(Vector3 mySegment_Start, Vector3 mySegmentEnd, const Transform* otherHexahedron);

			// **  自身が点の当たり判定  ** //
			/// <summary>
			/// 点と四角形が当たっているかを計算する	</summary>
			/// <param name = "myPoint">
			/// 自身として扱う点の座標値	</param>
			/// <param name = "otherRightTop">
			/// 相手として扱う四角形の右上頂点	</param>
			/// <param name = "otherLeftBottom">
			/// 相手として扱う線分の左下頂点	</param>
			/// <returns>
			/// 当たっていたらtrue、当たっていなければfalseを返す	</returns>
			static bool PointToQuadrangle(Vector3 myPoint, Vector3 otherRightTop, Vector3 otherLeftBottom);
	};
}

