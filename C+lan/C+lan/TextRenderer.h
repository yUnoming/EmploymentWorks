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

#include <vector>

namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	テキスト描画の処理を行うクラス	</summary>
		class TextRenderer : public EachFunction
		{
			private:
				// ----- structs / 構造体 ----- //
				/// <summary>
				///	テキスト情報	</summary>
				struct TextInfo
				{
					/// <summary>
					/// 使用するフォントのテクスチャ	</summary>
					ID3D11Texture2D* fontTexture;
					/// <summary>
					///	シェーダーがアクセスできるサブリソース	</summary>
					ID3D11ShaderResourceView* shaderResourceView;
				};


				// ----- variables / 変数 ----- //
				/// <summary>
				///	テキスト情報リスト	</summary>
				std::vector<TextInfo> m_TextInfoList;
				/// <summary>
				/// サンプラーの状態	</summary>
				ID3D11SamplerState* m_samplerState{};

				/// <summary>
				/// 前回表示されていたテキスト </summary>
				char m_lateText[101]{};

				/// <summary>
				///	テキストの長さ（文字数）	</summary>
				int m_textLength = 0;

				// ----- functions / 関数 ----- //
				/// <summary>
				/// 描画するテキストを作成 </summary>
				/// <param name="text">
				///	描画する文字	</param>
				/// <param name="textNum">
				/// 何文字目か	</param>
				/// <returns>
				/// 作成したテキスト情報	</returns>
				TextInfo CreateText(char text, int textNum);

				/// <summary>
				///	描画するテキストを作成（頂点バッファは作成しない）	</summary>
				/// <param name="text"> 
				///	描画する文字	</param>
				/// <param name="textNum">
				/// 何文字目か	</param>ee
				/// <returns>
				/// 作成したテキスト情報	</returns>
				TextInfo CreateTextWithoutVertexBuffer(char text, int textNum);

			public:
				//  ----- variables / 変数 ----- //
				/// <summary>
				/// 表示するテキスト </summary>
				const char* text = "";
				/// <summary>
				///	テキストの内容変更などで使う仮テキスト	</summary>
				char dummyText[101] = {};
				/// <summary>
				/// 文字サイズ </summary>
				Vector2 fontSize;
				/// <summary>
				///	テキストの左上頂点位置	</summary>
				Vector2 leftTopPoint = Vector2(0.f, 0.f);

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
				///	テキストの長さ（文字数）を取得	</summary>
				int GetTextLength() { return m_textLength; };
		};
	}
}