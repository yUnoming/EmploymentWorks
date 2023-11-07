#pragma once
/**
* @file		Transform.h
* @brief	TransformNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.02
*/
//  //
// @@t@CΜCN[h@@ //
//  //
#include "EachFunction.h"
#include "Vector3.h"


namespace PublicSystem
{
	/// <summary>
	///	ΚuEρ]Eε«³π\·NX	</summary>
	class Transform : public EachFunction
	{
	public:

		// ----- variables / Ο ----- //
		/// <summary>
		/// Κu	</summary>
		Vector3 Position = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		/// ρ]	</summary>
		Vector3 Rotation = Vector3(0.0f, 0.0f, 0.0f);
		/// <summary>
		///	ε«³	</summary>
		Vector3 Scale = Vector3(1.0f, 1.0f, 1.0f);
	};
}

