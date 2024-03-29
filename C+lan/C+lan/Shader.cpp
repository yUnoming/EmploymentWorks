#include "Shader.h"

void Ctlan::PublicSystem::Shader::Uninit()
{
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_vertexLayout->Release();
}

void Ctlan::PublicSystem::Shader::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_vertexLayout);
	// 頂点シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_vertexShader, nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_pixelShader, nullptr, 0);
}

void Ctlan::PublicSystem::Shader::Load(const char* vertexShader, const char* pixelShader)
{
	// 頂点シェーダーの作成
	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, vertexShader);
	// ピクセルシェーダーの作成
	Renderer::CreatePixelShader(&m_pixelShader, pixelShader);
	// 描画設定も行う
	Draw();
}
