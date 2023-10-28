#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "renderer.h"


// テキストを描画するためのクラス
class TextRenderer : public EachFunction
{
	private:
		// ----- variables / 変数 ----- //
		/// <summary>
		/// 使用するフォントのテクスチャ	</summary>
		ID3D11Texture2D* m_fontTexture{};
		/// <summary>
		/// サンプラーの状態	</summary>
		ID3D11SamplerState* m_samplerState{};
		/// <summary>
		/// シェーダーがアクセスできるサブリソース	</summary>
		ID3D11ShaderResourceView* m_shaderResourceView{};
		/// <summary>
		/// 頂点バッファ </summary>
		ID3D11Buffer* m_vertexBuffer{};

		/// <summary>
		/// 前回表示されていたテキスト </summary>
		const char* m_lateText;

	public:
		//  ----- variables / 変数 ----- //
		/// <summary>
		/// 表示するテキスト </summary>
		const char* m_text;

		// ----- functions / 関数 ----- //
		void Init();
		void Update();
		void Draw();

		/// <summary>
		/// 描画するテキストを作成する </summary>
		void Create_Text(const char* _text);
};

