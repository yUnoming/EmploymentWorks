#pragma once
/**
* @file		BoxCollider.h
* @brief	BoxColliderNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.01
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include "EachFunction.h"

/// <summary>
///	{bNXσΜ½θ»θNX	</summary>
class BoxCollider : public EachFunction
{
	public:
		// ----- functions / Φ ----- //
		/// <summary>
		/// ½θ»θΜvZ	</summary>
		/// <param name="other">
		/// ΥΛ΅½θΜ½θ»θ	</param>
		void CalcCollision(BoxCollider* other);

};

