#pragma once
/**
* @file		TextRenderer.h
* @brief	TextRendererクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "EachFunction.h"
#include "renderer.h"


/// <summary>
///	テキスト描画の処理を行うクラス	</summary>
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
		const char* text;

		// ----- functions / 関数 ----- //
		/// <summary>
		///	初期化	</summary>
		void Init();
		/// <summary>
		///	更新	</summary>
		void Update();
		/// <summary>
		///	描画	</summary>
		void Draw();

		/// <summary>
		/// 描画するテキストを作成する </summary>
		/// <param name="text">
		///	描画したい文字列	</param>
		void CreateText(const char* text);
};

