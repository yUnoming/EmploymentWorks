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

	// 頂点バッファの設定
	VERTEX_3D vertex[4];

	vertex[0].Position = DirectX::SimpleMath::Vector3(100.0f, 100.0f, 0.0f);
	vertex[0].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

	vertex[1].Position = DirectX::SimpleMath::Vector3(150.0f, 100.0f, 0.0f);
	vertex[1].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 0.0f);
	
	vertex[2].Position = DirectX::SimpleMath::Vector3(100.0f, 150.0f, 0.0f);
	vertex[2].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 1.0f);
	
	vertex[3].Position = DirectX::SimpleMath::Vector3(150.0f, 150.0f, 0.0f);
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

	Renderer::GetDevice()->CreateBuffer(&bufDesc, &subData, &m_vertexBuffer);
}

void TextRenderer::Update()
{
	// 表示するテキストが変更された？
	if (m_lateText == NULL || strcmp(m_text, m_lateText) != 0)
	{
		// 新たに表示するテキストを作成
		Create_Text(m_text);
	}

	// 現在表示されているテキストを保存する
	m_lateText = m_text;
}

void TextRenderer::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// テクスチャ描画に必要な情報を設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_shaderResourceView);
	Renderer::GetDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

	// プリミティブトポロジー設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

void TextRenderer::Create_Text(const char* _text)
{
	// ===== テキスト描画に必要な情報を取得 ===== //
	// フォントテクスチャ
	m_fontTexture = yUno_SystemManager::yUno_TextRendererManager::Get_FontTexture(_text);
	// シェーダーリソースビュー
	m_shaderResourceView = yUno_SystemManager::yUno_TextRendererManager::Get_ShaderResourceView(m_fontTexture);
}
