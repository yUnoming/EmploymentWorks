#include "TextRenderer.h"
#include "yUno_TextRendererManager.h"
#include "Transform.h"
#include <SimpleMath.h>
#include <WICTextureLoader.h>

using namespace PublicSystem;

void TextRenderer::Init()
{
	// サンプラー情報の設定
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.MaxAnisotropy = 1;
	samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// サンプラーの状態を作成
	Renderer::GetDevice()->CreateSamplerState(&samDesc, &m_samplerState);

	text = dummyText;
}

void TextRenderer::Update()
{
	// 表示するテキストが変更された？
	if (m_lateText == NULL || (strcmp(text, m_lateText) != 0 || strlen(text) != strlen(m_lateText)))
	{
		// ===== テキスト情報の作成 ===== //
		// テキストの長さ（文字数）
		m_textLength = strlen(text);
		
		// テキストの長さ分ループ
		for (int i = 0; i < m_textLength; i++)
		{
			// 既に別のテキストが格納されている？
			if (m_TextInfoList.size() - i > 0)
			{
				// 頂点バッファ以外のテキスト情報を作成
				TextInfo textInfo = CreateTextWithoutVertexBuffer(text[i], i);

				// 作成した情報をセット
				m_TextInfoList[i].fontTexture = textInfo.fontTexture;
				m_TextInfoList[i].shaderResourceView = textInfo.shaderResourceView;
			}
			else
				// 新たに表示するテキストを作成
				m_TextInfoList.push_back(CreateText(text[i], i));
		}

	}

	// 現在表示されているテキストを保存する
	ZeroMemory(m_lateText, sizeof(m_lateText));
	memcpy(m_lateText, text, strlen(text));
}

void TextRenderer::Draw()
{
	// テキストの文字数だけループ
	for (int i = 0; i < strlen(m_lateText); i++)
	{
		// マトリクス設定
		Renderer::SetWorldViewProjection2D();

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		m_TextInfoList[i].vertexBuffer = yUno_SystemManager::yUno_TextRendererManager::GetVertexBuffer(*this, i);
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_TextInfoList[i].vertexBuffer, &stride, &offset);

		// テクスチャ描画に必要な情報を設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextInfoList[i].shaderResourceView);
		Renderer::GetDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

		// プリミティブトポロジー設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// 描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

TextRenderer::TextInfo TextRenderer::CreateTextWithoutVertexBuffer(char text, int textNum)
{
	// ===== テキスト描画に必要な情報を作成 ===== //
	// フォントテクスチャ
	ID3D11Texture2D* fontTexture;
	fontTexture = yUno_SystemManager::yUno_TextRendererManager::GetFontTexture(text, textNum);
	// シェーダーリソースビュー
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = yUno_SystemManager::yUno_TextRendererManager::GetShaderResourceView(fontTexture);

	// ===== テキスト情報をセット ===== //
	TextInfo textInfo;
	textInfo.fontTexture = fontTexture;
	textInfo.shaderResourceView = shaderResourceView;

	// テキスト情報を返す
	return textInfo;
}

TextRenderer::TextInfo TextRenderer::CreateText(char text, int textNum)
{
	// ===== テキスト描画に必要な情報を作成 ===== //
	// フォントテクスチャ
	ID3D11Texture2D* fontTexture;
	fontTexture = yUno_SystemManager::yUno_TextRendererManager::GetFontTexture(text, textNum);
	// シェーダーリソースビュー
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = yUno_SystemManager::yUno_TextRendererManager::GetShaderResourceView(fontTexture);
	// 頂点バッファ
	ID3D11Buffer* vertexBuffer;
	vertexBuffer = yUno_SystemManager::yUno_TextRendererManager::GetVertexBuffer(*this, textNum);

	// ===== テキスト情報をセット ===== //
	TextInfo textInfo;
	textInfo.fontTexture = fontTexture;
	textInfo.shaderResourceView = shaderResourceView;
	textInfo.vertexBuffer = vertexBuffer;
	
	// テキスト情報を返す
	return textInfo;
}
