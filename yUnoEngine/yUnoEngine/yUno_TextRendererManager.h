#pragma once
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include <Shlwapi.h>
#include <vector>
#include "renderer.h"



namespace yUno_SystemManager
{
	// テキスト描画に必要な処理を行うクラス
	class yUno_TextRendererManager
	{
		private:
			// ----- variables / 変数 ----- //
			/// <summary>
			/// 作成されたフォント群 </summary>
			static std::vector<HFONT> m_CreateFonts;

			// 現在使用するフォントの要素数
			static int m_Now_Font_Index;

		public:
			// ----- functions / 関数 ----- //
			/// <summary>
			/// フォントテクスチャを作成し、取得 </summary>
			/// <param name = "_chara">
			/// 描画したい文字 </param>
			static ID3D11Texture2D* Get_FontTexture(const char* _chara);

			/// <summary>
			/// シェーダーリソースビューを作成し、取得 </summary>
			/// <param name = "_fontTexture">
			/// フォントテクスチャのポインター </param>
			static ID3D11ShaderResourceView* Get_ShaderResourceView(ID3D11Texture2D* _fontTexture);

			/// <summary>
			/// 作成したフォントをセットする </summary>
			/// <param name = "_addFont">
			/// 今回追加するフォント	</param>
			static void Set_Font(HFONT _addFont);
	};
}

