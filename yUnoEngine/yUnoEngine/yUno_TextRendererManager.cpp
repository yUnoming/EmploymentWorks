// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　ファイルのインクルード　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
#include "yUno_TextRendererManager.h"
#include "renderer.h"
#include <d3d11.h>
#include <iostream>


// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
// 　　staticメンバ変数の定義　　 //
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ //
std::vector<HFONT> yUno_SystemManager::yUno_TextRendererManager::m_CreateFonts;
int yUno_SystemManager::yUno_TextRendererManager::m_Now_Font_Index;



ID3D11Texture2D* yUno_SystemManager::yUno_TextRendererManager::Get_FontTexture(const char* _chara)
{
	// ===== 現在のウィンドウにフォントを適用 ===== //
	// デバイスコンテキスト取得
	HDC hdc = GetDC(NULL);
	// フォント取得
	HFONT oldFont = (HFONT)SelectObject(hdc, m_CreateFonts[m_Now_Font_Index]);

	// テクスチャに書き込む文字をセット
	UINT code = (UINT)*_chara;

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
	DeleteObject(m_CreateFonts[m_Now_Font_Index]);
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

	// テクスチャ2D変数
	ID3D11Texture2D* Texture2D;

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
	return Texture2D;
}

ID3D11ShaderResourceView* yUno_SystemManager::yUno_TextRendererManager::Get_ShaderResourceView(ID3D11Texture2D* _fontTexture)
{
	// シェーダーリソースビューの情報を設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// シェーダーリソースビュー変数
	ID3D11ShaderResourceView* Shader_Resource_View;

	// シェーダーリソースビューの作成
	HRESULT hr = Renderer::GetDevice()->CreateShaderResourceView(_fontTexture, &srvDesc, &Shader_Resource_View);

	// シェーダーリソースビューの作成に失敗した？
	if (hr != S_OK)
	{
		std::cout << "CreateShaderResourceView() Failed!!! ErrorCode：" << GetLastError() << std::endl;	// エラーログ表示
		return NULL;
	}

	return Shader_Resource_View;
}

void yUno_SystemManager::yUno_TextRendererManager::Set_Font(HFONT _addFont)
{
	// 引数で受け取ったフォントを追加する
	m_CreateFonts.push_back(_addFont);
}
