#pragma once
/**
* @file		yUno_TextRendererManager.h
* @brief	yUno_TextRendererManagerクラスのヘッダーファイル
* @author	Kojima, Kosei
* @date		2023.11.07
*/
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <Shlwapi.h>
#include <vector>
#include "renderer.h"
#include "TextRenderer.h"


namespace yUno_SystemManager
{
	/// <summary>
	/// テキスト描画を行うための処理を管理するクラス	</summary>
	class yUno_TextRendererManager
	{
		private:
			// ----- structs / 配列 ----- //
			/// <summary>
			///	フォントテクスチャ情報	</summary>
			struct FontTextureData
			{
				/// <summary>
				///	作成したフォントテクスチャの文字	</summary>
				char fontText;
				/// <summary>
				///	フォントテクスチャ	</summary>
				ID3D11Texture2D* fontTexture;
			};


			// ----- variables / 変数 ----- //
			/// <summary>
			/// 作成したフォント配列 </summary>
			static std::vector<HFONT> m_createFonts;
			/// <summary>
			/// 作成したフォントテクスチャ配列 </summary>
			static std::vector<FontTextureData> m_fontTextureDatas;

			// 現在使用するフォントの要素数
			static int m_nowFontIndex;

			// ----- functions / 関数 ----- //
			/// <summary>
			///	フォントテクスチャが既に作成しているか確認	</summary>
			/// <param name="text">
			///	検索する文字	</param>
			/// <returns>
			/// 作成済みのフォントテクスチャ、作成していなければnullptr</returns>
			static ID3D11Texture2D* CheckFontTexture(char text);

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			/// フォントテクスチャを作成し、取得 </summary>
			/// <param name = "text">
			/// 描画するテキスト </param>
			/// <param name="textNum">
			/// 何文字目か	</param>
			/// <returns>
			/// 作成したフォントテクスチャ	</returns>
			static ID3D11Texture2D* GetFontTexture(char text, int textNum);

			/// <summary>
			/// シェーダーリソースビューを作成し、取得 </summary>
			/// <param name = "fontTexture">
			/// フォントテクスチャのポインター </param>
			/// <returns>
			/// 作成したシェーダーリソースビュー	</returns>
			static ID3D11ShaderResourceView* GetShaderResourceView(ID3D11Texture2D* fontTexture);

			/// <summary>
			///	頂点バッファを作成し、取得	</summary>
			/// <param name="textData">
			///	テキスト情報	</param>
			/// <param name="fontNum">
			///	何文字目か（値が0 = 一文字目）	</param>
			/// <returns>
			/// 作成した頂点バッファ	</returns>
			static ID3D11Buffer* GetVertexBuffer(TextRenderer textData, int fontNum);

			/// <summary>
			/// 作成したフォントをセット </summary>
			/// <param name = "_addFont">
			/// 今回追加するフォント	</param>
			static void SetFont(HFONT addFont);
	};
}

