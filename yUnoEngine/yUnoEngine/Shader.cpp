#include "Shader.h"

void PublicSystem::Shader::UnInit()
{
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_vertexLayout->Release();
}

void PublicSystem::Shader::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_vertexLayout);
	// ���_�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_vertexShader, nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_pixelShader, nullptr, 0);
}

void PublicSystem::Shader::Load(const char* vertexShader, const char* pixelShader)
{
	// ���_�V�F�[�_�[�̍쐬
	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, vertexShader);
	// �s�N�Z���V�F�[�_�[�̍쐬
	Renderer::CreatePixelShader(&m_pixelShader, pixelShader);
}
