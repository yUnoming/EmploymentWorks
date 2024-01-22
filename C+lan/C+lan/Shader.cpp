#include "Shader.h"

void Ctlan::PublicSystem::Shader::Uninit()
{
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_vertexLayout->Release();
}

void Ctlan::PublicSystem::Shader::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_vertexLayout);
	// ���_�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_vertexShader, nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_pixelShader, nullptr, 0);
}

void Ctlan::PublicSystem::Shader::Load(const char* vertexShader, const char* pixelShader)
{
	// ���_�V�F�[�_�[�̍쐬
	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, vertexShader);
	// �s�N�Z���V�F�[�_�[�̍쐬
	Renderer::CreatePixelShader(&m_pixelShader, pixelShader);
	// �`��ݒ���s��
	Draw();
}
