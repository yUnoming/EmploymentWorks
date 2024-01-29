#include "SystemSceneManager.h"
#include "SystemNetWorkManager.h"
#include "SpectatorCamera.h"

#include "TextRenderer.h"
#include "SystemTextRendererManager.h"
#include "Transform.h"
#include <WICTextureLoader.h>


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
}

void TextRenderer::Update()
{
	// �\������e�L�X�g���ύX���ꂽ�H
	if (m_lateText == NULL || (strcmp(text, m_lateText) != 0 || strlen(text) != strlen(m_lateText)))
	{
		// ===== �e�L�X�g���̍쐬 ===== //
		// �e�L�X�g�̒����i�������j
		m_textLength = strlen(text);
		strncpy_s(dummyText, text, strlen(text));

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
				m_TextInfoList.push_back(CreateText(dummyText[i], i));
		}
		text = dummyText;
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
		m_TextInfoList[i].vertexBuffer = SystemManager::SystemTextRendererManager::GetVertexBuffer(*this, i);
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_TextInfoList[i].vertexBuffer, &stride, &offset);

		// �e�N�X�`���`��ɕK�v�ȏ���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextInfoList[i].shaderResourceView);
		Renderer::GetDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

		// �v���~�e�B�u�g�|���W�[�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �`��
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

// �f�o�b�O��
#if _DEBUG
	// ===== �e�L�X�g�̘g�̕\������ ===== //
	// �J�����擾
	EngineObject::SpectatorCamera* spectatorCamera = (Ctlan::EngineObject::SpectatorCamera*)SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject("SpectatorCamera");

	// ���̃R���|�[�l���g���ǉ�����Ă���I�u�W�F�N�g���N���b�N����Ă���H
	if (spectatorCamera && gameObject == spectatorCamera->GetClickedObject() ||
		SystemManager::SystemNetWorkManager::GetServer()->IsRockObject(gameObject->GetName()))
	{
		ID3D11ShaderResourceView* texture{};
		DirectX::CreateWICTextureFromFile(
			Renderer::GetDevice(),
			L"Assets/Textures/nullTexture.png",
			nullptr,
			&texture);

		// ----- ���_�쐬 ----- //
		VERTEX_3D vertex[8];
		// ��{�ځi��g�j
		// �g�̍��㒸�_
		vertex[0].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x, leftTopPoint.y, 0.0f);
		vertex[0].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[0].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
		// �g�̉E�㒸�_
		vertex[1].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x + fontSize.x * m_textLength, leftTopPoint.y, 0.0f);
		vertex[1].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[1].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 0.0f);

		// ��{�ځi�E�g�j
		// �g�̉E�㒸�_
		vertex[2] = vertex[1];
		// �g�̉E�����_
		vertex[3].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x + fontSize.x * m_textLength, leftTopPoint.y + fontSize.y, 0.0f);
		vertex[3].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[3].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

		// �O�{�ځi���g�j
		// �g�̉E�����_
		vertex[4] = vertex[3];
		// �g�̍������_
		vertex[5].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x, leftTopPoint.y + fontSize.y, 0.0f);
		vertex[5].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[5].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[5].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 1.0f);

		// �l�{�ځi���g�j
		// �g�̍������_
		vertex[6] = vertex[5];
		// �g�̍��㒸�_
		vertex[7] = vertex[0];

		// ���_�o�b�t�@�̍쐬
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.ByteWidth = sizeof(vertex);
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA initData = {};
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = vertex;

		ID3D11Buffer* vertexBuffer;
		HRESULT result = Renderer::GetDevice()->CreateBuffer(&vertexBufferDesc, &initData, &vertexBuffer);

		// ���_�o�b�t�@�̐ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// �e�N�X�`���`��ɕK�v�ȏ���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
		Renderer::GetDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		// �`��
		Renderer::GetDeviceContext()->Draw(8, 0);
	}
#endif
}

TextRenderer::TextInfo TextRenderer::CreateTextWithoutVertexBuffer(char text, int textNum)
{
	// ===== �e�L�X�g�`��ɕK�v�ȏ����쐬 ===== //
	// �t�H���g�e�N�X�`��
	ID3D11Texture2D* fontTexture;
	fontTexture = SystemManager::SystemTextRendererManager::GetFontTexture(text, textNum);
	// �V�F�[�_�[���\�[�X�r���[
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = SystemManager::SystemTextRendererManager::GetShaderResourceView(fontTexture);

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
	fontTexture = SystemManager::SystemTextRendererManager::GetFontTexture(text, textNum);
	// �V�F�[�_�[���\�[�X�r���[
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = SystemManager::SystemTextRendererManager::GetShaderResourceView(fontTexture);
	// ���_�o�b�t�@
	ID3D11Buffer* vertexBuffer;
	vertexBuffer = SystemManager::SystemTextRendererManager::GetVertexBuffer(*this, textNum);

	// ===== �e�L�X�g�����Z�b�g ===== //
	TextInfo textInfo;
	textInfo.fontTexture = fontTexture;
	textInfo.shaderResourceView = shaderResourceView;
	textInfo.vertexBuffer = vertexBuffer;
	
	// �e�L�X�g����Ԃ�
	return textInfo;
}
