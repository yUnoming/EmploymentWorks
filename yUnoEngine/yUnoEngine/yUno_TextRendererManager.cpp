// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_TextRendererManager.h"
#include "yUno_SceneManager.h"
#include "SpectatorCamera.h"
#include "Text.h"
#include "InputPartsName.h"
#include "renderer.h"

#include <d3d11.h>
#include <iostream>
#include <algorithm>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　staticメンバ変数の定義　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
std::vector<HFONT> yUno_SystemManager::yUno_TextRendererManager::m_createFonts;
std::vector<yUno_SystemManager::yUno_TextRendererManager::FontTextureData> yUno_SystemManager::yUno_TextRendererManager::m_fontTextureDatas;
int yUno_SystemManager::yUno_TextRendererManager::m_nowFontIndex;


ID3D11Texture2D* yUno_SystemManager::yUno_TextRendererManager::GetFontTexture(char text, int textNum)
{
	// ===== 既に作成されているかどうか確認 ==== //
	ID3D11Texture2D* Texture2D;
	Texture2D = CheckFontTexture(text);

	if (Texture2D)
		return Texture2D;

	// ===== 現在のウィンドウにフォントを適用 ===== //
	// デバイスコンテキスト取得
	HDC hdc = GetDC(NULL);
	// フォント取得
	HFONT oldFont = (HFONT)SelectObject(hdc, m_createFonts[m_nowFontIndex]);


	// テクスチャに書き込む文字をセット
	UINT code = (UINT)text;

	// ===== フォントビットマップ取得 ===== //
	TEXTMETRIC tm;		// テキストメトリック取得用変数
	// テキストメトリックを取得できなかった？
	if (!GetTextMetrics(hdc, &tm))
	{
		std::cout << "GetTextMetrics() Failed!!! ErrorCode：" << GetLastError() << std::endl;	// エラーログ表示
		return NULL;
	}

	// グリフメトリック取得用変数
	GLYPHMETRICS gm;
	CONST MAT2 Mat = { {0, 1}, {0, 0}, {0, 0}, {0, 1} };

	// ビットマップ取得に必要なバッファサイズを取得
	DWORD BufferSize = GetGlyphOutline(
		hdc,						// デバイスコンテキストへのハンドル
		code,						// データが返される文字
		GGO_GRAY4_BITMAP,			// 取得するデータ形式
		&gm,						// GLYPHMETRICS構造体へのポインター
		0,							// 関数がアウトライン文字に関する情報をコピーするバッファサイズ
		NULL,						// アウトライン文字に関する情報を受け取るバッファへのポインター
		&Mat						// MAT2構造体へのポインター
	);
	// 必要なバッファサイズ分のメモリを確保
	BYTE* Byte = new BYTE[BufferSize];

	// ビットマップ取得
	GetGlyphOutline(
		hdc,
		code,
		GGO_GRAY4_BITMAP,
		&gm,
		BufferSize,
		Byte,
		&Mat
	);

	// デバイスコンテキストとフォントハンドルの解放
	SelectObject(hdc, oldFont);
	DeleteObject(oldFont);
	ReleaseDC(NULL, hdc);

	// CPUで書き込みができるテクスチャを作成
	D3D11_TEXTURE2D_DESC Texture2D_Desc;
	memset(&Texture2D_Desc, 0, sizeof(Texture2D_Desc));
	Texture2D_Desc.Width = gm.gmCellIncX;
	Texture2D_Desc.Height = tm.tmHeight;
	Texture2D_Desc.MipLevels = 1;
	Texture2D_Desc.ArraySize = 1;

	// RGBA(255,255,255,255)タイプ
	Texture2D_Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Texture2D_Desc.SampleDesc.Count = 1;
	// 動的（書き込みするための必須条件）
	Texture2D_Desc.Usage = D3D11_USAGE_DYNAMIC;
	// シェーダーリソースとして使う
	Texture2D_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	// CPUからアクセスして書き込みOK
	Texture2D_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// 2Dテクスチャ作成
	HRESULT hr = Renderer::GetDevice()->CreateTexture2D(
		&Texture2D_Desc,			// D3D11_TEXTURE2D_DESC構造体へのポインター（設定したい内容を渡す）
		NULL,						// D3D11_SUBRESOURCE_DATA構造体へのポインター（リソースがマルチサンプリングの場合はNULL）
		&Texture2D					// ID3D11Texture2Dへのポインター（作成したテクスチャを受け取る）
	);

	// 2Dテクスチャの作成に失敗した？
	if (hr != S_OK)
	{
		std::cout << "CreateTexture2D() Failed!!! ErrorCode：" << GetLastError() << std::endl;	// エラーログ表示
		return NULL;
	}

	// サブリソース取得用変数
	D3D11_MAPPED_SUBRESOURCE Mapped_SubResource;
	// サブリソース取得（フォント情報をテクスチャに書き込む部分）
	hr = Renderer::GetDeviceContext()->Map(
		Texture2D,					// ID3D11Resorceへのポインター
		0,							// サブリソースのインデックス番号
		D3D11_MAP_WRITE_DISCARD,	// 読み取り、書き込み方法を指定するD3D11_MAP型の値
		0,							// CPUが実行する処理を指定するフラグ
		&Mapped_SubResource			// D3D11_MAPPED_SUBRESOURCE構造体へのポインター
	);

	// 2Dテクスチャの作成に失敗した？
	if (hr != S_OK)
	{
		std::cout << "Map() Failed!!! ErrorCode：" << GetLastError() << std::endl;	// エラーログ表示
		return NULL;
	}

	// サブリソース書き込み（ここでテクスチャに書き込む）
	BYTE* Bits = (BYTE*)Mapped_SubResource.pData;

	// フォント情報書き込み
	int Write_PosX = gm.gmptGlyphOrigin.x;					// 書き出し位置のX座標
	int Write_PosY = tm.tmAscent - gm.gmptGlyphOrigin.y;	// 書き出し位置のY座標
	int Bitmap_Weight =
		gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;	// フォントビットマップの幅
	int Bitmap_Height = gm.gmBlackBoxY;						// フォントビットマップの高さ
	int Level = 17;											// α値の段階
	int PosX, PosY;											// 座標
	DWORD Alpha, Color;										// 色・α値

	memset(Bits, 0, Mapped_SubResource.RowPitch * tm.tmHeight);

	// ===== テクスチャにフォントビットマップを書き込む処理 ===== //
	for (PosY = Write_PosY; PosY < Write_PosY + Bitmap_Height; PosY++)
	{
		for (PosX = Write_PosX; PosX < Write_PosX + Bitmap_Weight; PosX++)
		{
			Alpha =
				(255 * Byte[PosX - Write_PosX + Bitmap_Weight * (PosY - Write_PosY)]) / (Level - 1);
			
			Color = 0x00ffffff | (Alpha << 24);
			memcpy(
				(BYTE*)Bits + Mapped_SubResource.RowPitch * PosY + 4 * PosX,
				&Color,
				sizeof(DWORD)
			);
		}
	}

	Renderer::GetDeviceContext()->Unmap(Texture2D, 0);

	// 作成したフォントテクスチャを格納
	FontTextureData fontTextureData;
	fontTextureData.fontText = text;
	fontTextureData.fontTexture = Texture2D;
	m_fontTextureDatas.push_back(fontTextureData);

	return Texture2D;
}

ID3D11ShaderResourceView* yUno_SystemManager::yUno_TextRendererManager::GetShaderResourceView(ID3D11Texture2D* fontTexture)
{
	// シェーダーリソースビューの情報を設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// シェーダーリソースビュー変数
	ID3D11ShaderResourceView* shaderResourceView;

	// シェーダーリソースビューの作成
	HRESULT hr = Renderer::GetDevice()->CreateShaderResourceView(fontTexture, &srvDesc, &shaderResourceView);

	// シェーダーリソースビューの作成に失敗した？
	if (hr != S_OK)
	{
		std::cout << "CreateShaderResourceView() Failed!!! ErrorCode：" << GetLastError() << std::endl;	// エラーログ表示
		return NULL;
	}

	return shaderResourceView;
}

ID3D11Buffer* yUno_SystemManager::yUno_TextRendererManager::GetVertexBuffer(TextRenderer textData, int fontNum)
{
	// 頂点バッファの設定
	VERTEX_3D vertex[4];
	// 左上
	vertex[0].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y, 0.0f);
	vertex[0].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	// 右上
	vertex[1].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y, 0.0f);
	vertex[1].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 0.0f);
	// 左下
	vertex[2].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y + textData.fontSize.y, 0.0f);
	vertex[2].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 1.0f);
	// 右下
	vertex[3].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y + textData.fontSize.y, 0.0f);
	vertex[3].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

	// 頂点バッファを作成
	D3D11_BUFFER_DESC bufDesc;
	ZeroMemory(&bufDesc, sizeof(bufDesc));
	bufDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufDesc.ByteWidth = sizeof(vertex);
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = vertex;

	// 戻り値となるバーテックスバッファ
	ID3D11Buffer* vertexBuffer;
	Renderer::GetDevice()->CreateBuffer(&bufDesc, &subData, &vertexBuffer);

	return vertexBuffer;
}

void yUno_SystemManager::yUno_TextRendererManager::SetFont(HFONT addFont)
{
	// 引数で受け取ったフォントを追加する
	m_createFonts.push_back(addFont);
}

void test(std::wstring a)
{

}

// 文字を小文字に変換するヘルパー関数
wchar_t toLower(wchar_t ch) {
	return towlower(ch);
}

#include "KeyInput.h"
void yUno_SystemManager::yUno_TextRendererManager::Input(int keyCode)
{
	// 入力可能状態のテキストが存在する？
	SpectatorCamera* specCamera = yUno_SceneManager::GetEditScene()->GetSceneObject<SpectatorCamera>("SpectatorCamera");
	if (!specCamera)return;
	GameObject* obj = specCamera->GetClickedObject();
	if (!obj)return;
	Text* text = obj->GetComponent<Text>();
	if (text)
	{
		// ===== テキストに文字入力 ===== //
		// スキャンコードを文字列に変換
		wchar_t typeChar[256];
		int result = GetKeyNameTextW(keyCode << 16, typeChar, sizeof(typeChar) / sizeof(wchar_t));

		// 文字として扱えるキーが入力された
		if (result == 1)
		{
			// シフトキーが押されていない？
			if(KeyInput::GetKeyUp(LeftShift) && KeyInput::GetKeyUp(RightShift))
				// 大文字を小文字に変換
				std::transform(typeChar, typeChar + result, typeChar, toLower);

			// バッファサイズの取得
			int bufferSize = WideCharToMultiByte(CP_UTF8, 0, std::wstring(typeChar).c_str(), -1, nullptr, 0, nullptr, nullptr);
			// バッファの確保
			char* charBuffer = new char[bufferSize];
			// ワイド文字列からマルチバイト文字列に変換
			WideCharToMultiByte(CP_UTF8, 0, std::wstring(typeChar).c_str(), -1, charBuffer, bufferSize, nullptr, nullptr);
			
			// テキストに文字を追加
			text->AddText(charBuffer);
			return;
		}

		// ===== その他テキスト関係の処理 ===== //
		switch (keyCode)
		{
			// バックスペースキーの入力
			case KeyName::BackSpace:
				text->DeleteText();	// テキストの末尾を削除
				break;
			// スペースキーの入力
			case KeyName::Space:
				text->AddText(" "); // テキストに空白文字を追加
				break;
		}
	}
}

ID3D11Texture2D* yUno_SystemManager::yUno_TextRendererManager::CheckFontTexture(char text)
{
	for (auto fontTexture : m_fontTextureDatas)
	{
		if (fontTexture.fontText == text)
		{
			return fontTexture.fontTexture;
		}
	}
	return nullptr;
}
