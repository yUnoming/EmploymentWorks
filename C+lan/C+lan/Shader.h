#pragma once
/**
* @file		Component.h
* @brief	Componentクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.27
*/

// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "renderer.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	シェーダーを表すクラス	</summary>
		class Shader : public EachFunction
		{
			private:
				// ----- variables / 変数 ----- //
				/// <summary>
				///	頂点シェーダー	</summary>
				ID3D11VertexShader* m_vertexShader{};
				/// <summary>
				///	ピクセルシェーダー	</summary>
				ID3D11PixelShader* m_pixelShader{};
				/// <summary>
				///	頂点レイアウト	</summary>
				ID3D11InputLayout* m_vertexLayout{};

			public:
				// ----- functions / 関数 ----- //
				/// <summary>
				/// 終了		</summary>
				void Uninit() override;
				/// <summary>
				/// 描画		</summary>
				void Draw() override;

				/// <summary>
				///	シェーダーを読み込む	</summary>
				/// <param name="vertexShader">
				///	頂点シェーダーのファイルパス	</param>
				/// <param name="pixelShader">
				///	ピクセルシェーダーのファイルパス	</param>
				void Load(const char* vertexShader, const char* pixelShader);
		};
	}
}