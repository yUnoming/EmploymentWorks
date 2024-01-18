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
#include <SimpleMath.h>

namespace PublicSystem
{
	/// <summary>
	///	ΚuEρ]Eε«³π\·NX	</summary>
	class Transform : public EachFunction
	{
		public:
			// ----- variables / Ο ----- //
			/// <summary>
			/// [hΐW	</summary>
			Vector3 position = Vector3(0.0f, 0.0f, 0.0f);
			/// <summary>
			/// [JΐW	</summary>
			Vector3 localPosition = Vector3(0.0f, 0.0f, 0.0f);

			/// <summary>
			/// ρ]	</summary>
			Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f);
			/// <summary>
			///	ε«³	</summary>
			Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);

			// ----- functions / Φ ----- //
			/// <summary>
			///	`ζ	</summary>
			void Draw();
			/// <summary>
			/// [hsρπζΎ	</summary>
			/// <returns>[hsρ</returns>
			DirectX::SimpleMath::Matrix GetWorldMatrix(Transform* childTransform);

			/// <summary>
			///	Transform^ΖΜγόIy[^[	</summary>
			/// <param name="other">
			///	Transform^ΜIuWFNg	</param>
			/// <returns>
			///	γόγΜTransformξρ	</returns>
			Transform& operator=(const Transform& other);
	};
}

