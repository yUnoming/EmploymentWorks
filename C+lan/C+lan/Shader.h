#pragma once
/**
* @file		Component.h
* @brief	ComponentNXΜwb_[t@C
* @author	Kojima, Kosei
* @date		2023.11.27
*/

//  //
// @@t@CΜCN[h@@ //
//  //
#include "EachFunction.h"
#include "renderer.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	VF[_[π\·NX	</summary>
		class Shader : public EachFunction
		{
			private:
				// ----- variables / Ο ----- //
				/// <summary>
				///	Έ_VF[_[	</summary>
				ID3D11VertexShader* m_vertexShader{};
				/// <summary>
				///	sNZVF[_[	</summary>
				ID3D11PixelShader* m_pixelShader{};
				/// <summary>
				///	Έ_CAEg	</summary>
				ID3D11InputLayout* m_vertexLayout{};

				// ----- functions / Φ ----- //
				/// <summary>
				/// IΉ		</summary>
				void Uninit() override;
				/// <summary>
				/// `ζ		</summary>
				void Draw() override;

			public:
				// ----- functions / Φ ----- //
				/// <summary>
				///	VF[_[πΗέή	</summary>
				/// <param name="vertexShader">
				///	Έ_VF[_[Μt@CpX	</param>
				/// <param name="pixelShader">
				///	sNZVF[_[Μt@CpX	</param>
				void Load(const char* vertexShader, const char* pixelShader);
		};
	}
}