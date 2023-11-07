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


namespace yUno_SystemManager
{
	/// <summary>
	/// テキスト描画を行うための処理を管理するクラス	</summary>
	class yUno_TextRendererManager
	{
		private:
			// ----- variables / 変数 ----- //
			/// <summary>
			/// 作成されたフォント群 </summary>
			static std::vector<HFONT> m_createFonts;

			// 現在使用するフォントの要素数
			static int m_nowFontIndex;

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			/// フォントテクスチャを作成し、取得 </summary>
			/// <param name = "text">
			/// 描画したい文字 </param>
			static ID3D11Texture2D* GetFontTexture(const char* text);

			/// <summary>
			/// シェーダーリソースビューを作成し、取得 </summary>
			/// <param name = "fontTexture">
			/// フォントテクスチャのポインター </param>
			static ID3D11ShaderResourceView* GetShaderResourceView(ID3D11Texture2D* fontTexture);

			/// <summary>
			/// 作成したフォントをセットする </summary>
			/// <param name = "_addFont">
			/// 今回追加するフォント	</param>
			static void SetFont(HFONT addFont);
	};
}

