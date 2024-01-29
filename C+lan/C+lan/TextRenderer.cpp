#include "SystemSceneManager.h"
#include "SystemNetWorkManager.h"
#include "SpectatorCamera.h"

#include "TextRenderer.h"
#include "SystemTextRendererManager.h"
#include "Transform.h"
#include <WICTextureLoader.h>


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
}

void TextRenderer::Update()
{
	// 表示するテキストが変更された？
	if (m_lateText == NULL || (strcmp(text, m_lateText) != 0 || strlen(text) != strlen(m_lateText)))
	{
		// ===== テキスト情報の作成 ===== //
		// テキストの長さ（文字数）
		m_textLength = strlen(text);
		strncpy_s(dummyText, text, strlen(text));

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
				m_TextInfoList.push_back(CreateText(dummyText[i], i));
		}
		text = dummyText;
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
		m_TextInfoList[i].vertexBuffer = SystemManager::SystemTextRendererManager::GetVertexBuffer(*this, i);
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_TextInfoList[i].vertexBuffer, &stride, &offset);

		// テクスチャ描画に必要な情報を設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_TextInfoList[i].shaderResourceView);
		Renderer::GetDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

		// プリミティブトポロジー設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// 描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}

// デバッグ時
#if _DEBUG
	// ===== テキストの枠の表示処理 ===== //
	// カメラ取得
	EngineObject::SpectatorCamera* spectatorCamera = (Ctlan::EngineObject::SpectatorCamera*)SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject("SpectatorCamera");

	// このコンポーネントが追加されているオブジェクトがクリックされている？
	if (spectatorCamera && gameObject == spectatorCamera->GetClickedObject() ||
		SystemManager::SystemNetWorkManager::GetServer()->IsRockObject(gameObject->GetName()))
	{
		ID3D11ShaderResourceView* texture{};
		DirectX::CreateWICTextureFromFile(
			Renderer::GetDevice(),
			L"Assets/Textures/nullTexture.png",
			nullptr,
			&texture);

		// ----- 頂点作成 ----- //
		VERTEX_3D vertex[8];
		// 一本目（上枠）
		// 枠の左上頂点
		vertex[0].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x, leftTopPoint.y, 0.0f);
		vertex[0].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[0].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
		// 枠の右上頂点
		vertex[1].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x + fontSize.x * m_textLength, leftTopPoint.y, 0.0f);
		vertex[1].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[1].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 0.0f);

		// 二本目（右枠）
		// 枠の右上頂点
		vertex[2] = vertex[1];
		// 枠の右下頂点
		vertex[3].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x + fontSize.x * m_textLength, leftTopPoint.y + fontSize.y, 0.0f);
		vertex[3].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[3].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

		// 三本目（下枠）
		// 枠の右下頂点
		vertex[4] = vertex[3];
		// 枠の左下頂点
		vertex[5].Position = DirectX::SimpleMath::Vector3(
			leftTopPoint.x, leftTopPoint.y + fontSize.y, 0.0f);
		vertex[5].Normal = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		vertex[5].Diffuse = DirectX::XMFLOAT4(Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName())));
		vertex[5].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 1.0f);

		// 四本目（左枠）
		// 枠の左下頂点
		vertex[6] = vertex[5];
		// 枠の左上頂点
		vertex[7] = vertex[0];

		// 頂点バッファの作成
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

		// 頂点バッファの設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// テクスチャ描画に必要な情報を設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
		Renderer::GetDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);

		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		// 描画
		Renderer::GetDeviceContext()->Draw(8, 0);
	}
#endif
}

TextRenderer::TextInfo TextRenderer::CreateTextWithoutVertexBuffer(char text, int textNum)
{
	// ===== テキスト描画に必要な情報を作成 ===== //
	// フォントテクスチャ
	ID3D11Texture2D* fontTexture;
	fontTexture = SystemManager::SystemTextRendererManager::GetFontTexture(text, textNum);
	// シェーダーリソースビュー
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = SystemManager::SystemTextRendererManager::GetShaderResourceView(fontTexture);

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
	fontTexture = SystemManager::SystemTextRendererManager::GetFontTexture(text, textNum);
	// シェーダーリソースビュー
	ID3D11ShaderResourceView* shaderResourceView;
	shaderResourceView = SystemManager::SystemTextRendererManager::GetShaderResourceView(fontTexture);
	// 頂点バッファ
	ID3D11Buffer* vertexBuffer;
	vertexBuffer = SystemManager::SystemTextRendererManager::GetVertexBuffer(*this, textNum);

	// ===== テキスト情報をセット ===== //
	TextInfo textInfo;
	textInfo.fontTexture = fontTexture;
	textInfo.shaderResourceView = shaderResourceView;
	textInfo.vertexBuffer = vertexBuffer;
	
	// テキスト情報を返す
	return textInfo;
}
