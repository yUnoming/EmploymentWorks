#include "TextRenderer.h"
#include "yUno_TextRendererManager.h"
#include "Transform.h"
#include <SimpleMath.h>
#include <WICTextureLoader.h>

using namespace PublicSystem;

void TextRenderer::Init()
{
	// �T���v���[���̐ݒ�
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.MaxAnisotropy = 1;
	samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// �T���v���[�̏�Ԃ��쐬
	Renderer::GetDevice()->CreateSamplerState(&samDesc, &m_samplerState);

	text = dummyText;
}

void TextRenderer::Update()
{
	// �\������e�L�X�g���ύX���ꂽ�H
	if (m_lateText == NULL || (strcmp(text, m_lateText) != 0 || strlen(text) != strlen(m_lateText)))
	{
		// ===== �e�L�X�g���̍쐬 ===== //
		// �e�L�X�g�̒����i�������j
		m_textLength = strlen(text);
		
		// �e�L�X�g�̒��������[�v
		for (int i = 0; i < m_textLength; i++)
		{
			// ���ɕʂ̃e�L�X�g���i�[����Ă���H
			if (m_TextInfoList.size() - i > 0)
			{
				// ���_�o�b�t�@�ȊO�̃e�L�X�g�����쐬
				TextInfo textInfo = CreateTextWithoutVertexBuffer(text[i], i);

				// �쐬���������Z�b�g
				m_TextInfoList[i].fontTexture = textInfo.fontTexture;
				m_TextInfoList[i].shaderResourceView = textInfo.shaderResourceView;
			}
			else
				// �V���ɕ\������e�L�X�g���쐬
				m_TextInfoList.push_back(CreateText(text[i], i));
		}

	}

	// ���ݕ\������Ă���e�L�X�g��ۑ�����
	ZeroMemory(m_lateText, sizeof(m_lateText));
	memcpy(m_lateText, text, strlen(text));
}

void TextRenderer::Draw()
{
	// �e�L�X�g�̕������������[�v
	for (int i = 0; i < strlen(m_lateText); i++)
	{
		// �}�g���N�X�ݒ�
		Renderer::SetWorldViewProjection2D();

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		m_TextInfoList[i].vertexBuffer = yUno_SystemManager::yUno_TextRendererManager::GetVertexBuffer(*this, i);
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_TextInfoList[i].vertexBuffer, &stride, &offset);

		// �e�N�X�`���`��ɕK�v�ȏ���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextInfoList[i].shaderResourceView);
		Renderer::GetDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

		// �v���~�e�B�u�g�|���W�[�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �`��
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

TextRenderer::TextInfo TextRenderer::CreateTextWithoutVertexBuffer(char text, int textNum)
{
	// ===== �e�L�X�g�`��ɕK�v�ȏ����쐬 ===== //
	// �t�H���g�e�N�X�`��
	ID3D11Texture2D* fontTexture;
	fontTexture = yUno_SystemManager::yUno_TextRendererManager::GetFontTexture(text, textNum);
	// �V�F�[�_�[���\�[�X�r���[
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = yUno_SystemManager::yUno_TextRendererManager::GetShaderResourceView(fontTexture);

	// ===== �e�L�X�g�����Z�b�g ===== //
	TextInfo textInfo;
	textInfo.fontTexture = fontTexture;
	textInfo.shaderResourceView = shaderResourceView;

	// �e�L�X�g����Ԃ�
	return textInfo;
}

TextRenderer::TextInfo TextRenderer::CreateText(char text, int textNum)
{
	// ===== �e�L�X�g�`��ɕK�v�ȏ����쐬 ===== //
	// �t�H���g�e�N�X�`��
	ID3D11Texture2D* fontTexture;
	fontTexture = yUno_SystemManager::yUno_TextRendererManager::GetFontTexture(text, textNum);
	// �V�F�[�_�[���\�[�X�r���[
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = yUno_SystemManager::yUno_TextRendererManager::GetShaderResourceView(fontTexture);
	// ���_�o�b�t�@
	ID3D11Buffer* vertexBuffer;
	vertexBuffer = yUno_SystemManager::yUno_TextRendererManager::GetVertexBuffer(*this, textNum);

	// ===== �e�L�X�g�����Z�b�g ===== //
	TextInfo textInfo;
	textInfo.fontTexture = fontTexture;
	textInfo.shaderResourceView = shaderResourceView;
	textInfo.vertexBuffer = vertexBuffer;
	
	// �e�L�X�g����Ԃ�
	return textInfo;
}
