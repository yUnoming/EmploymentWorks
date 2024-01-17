// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_TextRendererManager.h"
#include "yUno_SceneManager.h"
#include "SpectatorCamera.h"
#include "Text.h"
#include "InputPartsName.h"
#include "renderer.h"

#include <d3d11.h>
#include <iostream>
#include <algorithm>


// ������������������������������ //
// �@�@static�����o�ϐ��̒�`�@�@ //
// ������������������������������ //
std::vector<HFONT> yUno_SystemManager::yUno_TextRendererManager::m_createFonts;
std::vector<yUno_SystemManager::yUno_TextRendererManager::FontTextureData> yUno_SystemManager::yUno_TextRendererManager::m_fontTextureDatas;
int yUno_SystemManager::yUno_TextRendererManager::m_nowFontIndex;


ID3D11Texture2D* yUno_SystemManager::yUno_TextRendererManager::GetFontTexture(char text, int textNum)
{
	// ===== ���ɍ쐬����Ă��邩�ǂ����m�F ==== //
	ID3D11Texture2D* Texture2D;
	Texture2D = CheckFontTexture(text);

	if (Texture2D)
		return Texture2D;

	// ===== ���݂̃E�B���h�E�Ƀt�H���g��K�p ===== //
	// �f�o�C�X�R���e�L�X�g�擾
	HDC hdc = GetDC(NULL);
	// �t�H���g�擾
	HFONT oldFont = (HFONT)SelectObject(hdc, m_createFonts[m_nowFontIndex]);


	// �e�N�X�`���ɏ������ޕ������Z�b�g
	UINT code = (UINT)text;

	// ===== �t�H���g�r�b�g�}�b�v�擾 ===== //
	TEXTMETRIC tm;		// �e�L�X�g���g���b�N�擾�p�ϐ�
	// �e�L�X�g���g���b�N���擾�ł��Ȃ������H
	if (!GetTextMetrics(hdc, &tm))
	{
		std::cout << "GetTextMetrics() Failed!!! ErrorCode�F" << GetLastError() << std::endl;	// �G���[���O�\��
		return NULL;
	}

	// �O���t���g���b�N�擾�p�ϐ�
	GLYPHMETRICS gm;
	CONST MAT2 Mat = { {0, 1}, {0, 0}, {0, 0}, {0, 1} };

	// �r�b�g�}�b�v�擾�ɕK�v�ȃo�b�t�@�T�C�Y���擾
	DWORD BufferSize = GetGlyphOutline(
		hdc,						// �f�o�C�X�R���e�L�X�g�ւ̃n���h��
		code,						// �f�[�^���Ԃ���镶��
		GGO_GRAY4_BITMAP,			// �擾����f�[�^�`��
		&gm,						// GLYPHMETRICS�\���̂ւ̃|�C���^�[
		0,							// �֐����A�E�g���C�������Ɋւ�������R�s�[����o�b�t�@�T�C�Y
		NULL,						// �A�E�g���C�������Ɋւ�������󂯎��o�b�t�@�ւ̃|�C���^�[
		&Mat						// MAT2�\���̂ւ̃|�C���^�[
	);
	// �K�v�ȃo�b�t�@�T�C�Y���̃��������m��
	BYTE* Byte = new BYTE[BufferSize];

	// �r�b�g�}�b�v�擾
	GetGlyphOutline(
		hdc,
		code,
		GGO_GRAY4_BITMAP,
		&gm,
		BufferSize,
		Byte,
		&Mat
	);

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̉��
	SelectObject(hdc, oldFont);
	DeleteObject(oldFont);
	ReleaseDC(NULL, hdc);

	// CPU�ŏ������݂��ł���e�N�X�`�����쐬
	D3D11_TEXTURE2D_DESC Texture2D_Desc;
	memset(&Texture2D_Desc, 0, sizeof(Texture2D_Desc));
	Texture2D_Desc.Width = gm.gmCellIncX;
	Texture2D_Desc.Height = tm.tmHeight;
	Texture2D_Desc.MipLevels = 1;
	Texture2D_Desc.ArraySize = 1;

	// RGBA(255,255,255,255)�^�C�v
	Texture2D_Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Texture2D_Desc.SampleDesc.Count = 1;
	// ���I�i�������݂��邽�߂̕K�{�����j
	Texture2D_Desc.Usage = D3D11_USAGE_DYNAMIC;
	// �V�F�[�_�[���\�[�X�Ƃ��Ďg��
	Texture2D_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	// CPU����A�N�Z�X���ď�������OK
	Texture2D_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// 2D�e�N�X�`���쐬
	HRESULT hr = Renderer::GetDevice()->CreateTexture2D(
		&Texture2D_Desc,			// D3D11_TEXTURE2D_DESC�\���̂ւ̃|�C���^�[�i�ݒ肵�������e��n���j
		NULL,						// D3D11_SUBRESOURCE_DATA�\���̂ւ̃|�C���^�[�i���\�[�X���}���`�T���v�����O�̏ꍇ��NULL�j
		&Texture2D					// ID3D11Texture2D�ւ̃|�C���^�[�i�쐬�����e�N�X�`�����󂯎��j
	);

	// 2D�e�N�X�`���̍쐬�Ɏ��s�����H
	if (hr != S_OK)
	{
		std::cout << "CreateTexture2D() Failed!!! ErrorCode�F" << GetLastError() << std::endl;	// �G���[���O�\��
		return NULL;
	}

	// �T�u���\�[�X�擾�p�ϐ�
	D3D11_MAPPED_SUBRESOURCE Mapped_SubResource;
	// �T�u���\�[�X�擾�i�t�H���g�����e�N�X�`���ɏ������ޕ����j
	hr = Renderer::GetDeviceContext()->Map(
		Texture2D,					// ID3D11Resorce�ւ̃|�C���^�[
		0,							// �T�u���\�[�X�̃C���f�b�N�X�ԍ�
		D3D11_MAP_WRITE_DISCARD,	// �ǂݎ��A�������ݕ��@���w�肷��D3D11_MAP�^�̒l
		0,							// CPU�����s���鏈�����w�肷��t���O
		&Mapped_SubResource			// D3D11_MAPPED_SUBRESOURCE�\���̂ւ̃|�C���^�[
	);

	// 2D�e�N�X�`���̍쐬�Ɏ��s�����H
	if (hr != S_OK)
	{
		std::cout << "Map() Failed!!! ErrorCode�F" << GetLastError() << std::endl;	// �G���[���O�\��
		return NULL;
	}

	// �T�u���\�[�X�������݁i�����Ńe�N�X�`���ɏ������ށj
	BYTE* Bits = (BYTE*)Mapped_SubResource.pData;

	// �t�H���g��񏑂�����
	int Write_PosX = gm.gmptGlyphOrigin.x;					// �����o���ʒu��X���W
	int Write_PosY = tm.tmAscent - gm.gmptGlyphOrigin.y;	// �����o���ʒu��Y���W
	int Bitmap_Weight =
		gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;	// �t�H���g�r�b�g�}�b�v�̕�
	int Bitmap_Height = gm.gmBlackBoxY;						// �t�H���g�r�b�g�}�b�v�̍���
	int Level = 17;											// ���l�̒i�K
	int PosX, PosY;											// ���W
	DWORD Alpha, Color;										// �F�E���l

	memset(Bits, 0, Mapped_SubResource.RowPitch * tm.tmHeight);

	// ===== �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v���������ޏ��� ===== //
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

	// �쐬�����t�H���g�e�N�X�`�����i�[
	FontTextureData fontTextureData;
	fontTextureData.fontText = text;
	fontTextureData.fontTexture = Texture2D;
	m_fontTextureDatas.push_back(fontTextureData);

	return Texture2D;
}

ID3D11ShaderResourceView* yUno_SystemManager::yUno_TextRendererManager::GetShaderResourceView(ID3D11Texture2D* fontTexture)
{
	// �V�F�[�_�[���\�[�X�r���[�̏���ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// �V�F�[�_�[���\�[�X�r���[�ϐ�
	ID3D11ShaderResourceView* shaderResourceView;

	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	HRESULT hr = Renderer::GetDevice()->CreateShaderResourceView(fontTexture, &srvDesc, &shaderResourceView);

	// �V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s�����H
	if (hr != S_OK)
	{
		std::cout << "CreateShaderResourceView() Failed!!! ErrorCode�F" << GetLastError() << std::endl;	// �G���[���O�\��
		return NULL;
	}

	return shaderResourceView;
}

ID3D11Buffer* yUno_SystemManager::yUno_TextRendererManager::GetVertexBuffer(TextRenderer textData, int fontNum)
{
	// ���_�o�b�t�@�̐ݒ�
	VERTEX_3D vertex[4];
	// ����
	vertex[0].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y, 0.0f);
	vertex[0].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
	// �E��
	vertex[1].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y, 0.0f);
	vertex[1].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 0.0f);
	// ����
	vertex[2].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y + textData.fontSize.y, 0.0f);
	vertex[2].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = DirectX::SimpleMath::Vector2(0.0f, 1.0f);
	// �E��
	vertex[3].Position = DirectX::SimpleMath::Vector3(
		textData.leftTopPoint.x + textData.fontSize.x + textData.fontSize.x * fontNum, textData.leftTopPoint.y + textData.fontSize.y, 0.0f);
	vertex[3].Normal = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

	// ���_�o�b�t�@���쐬
	D3D11_BUFFER_DESC bufDesc;
	ZeroMemory(&bufDesc, sizeof(bufDesc));
	bufDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufDesc.ByteWidth = sizeof(vertex);
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(subData));
	subData.pSysMem = vertex;

	// �߂�l�ƂȂ�o�[�e�b�N�X�o�b�t�@
	ID3D11Buffer* vertexBuffer;
	Renderer::GetDevice()->CreateBuffer(&bufDesc, &subData, &vertexBuffer);

	return vertexBuffer;
}

void yUno_SystemManager::yUno_TextRendererManager::SetFont(HFONT addFont)
{
	// �����Ŏ󂯎�����t�H���g��ǉ�����
	m_createFonts.push_back(addFont);
}

void test(std::wstring a)
{

}

// �������������ɕϊ�����w���p�[�֐�
wchar_t toLower(wchar_t ch) {
	return towlower(ch);
}

#include "KeyInput.h"
void yUno_SystemManager::yUno_TextRendererManager::Input(int keyCode)
{
	// ���͉\��Ԃ̃e�L�X�g�����݂���H
	SpectatorCamera* specCamera = yUno_SceneManager::GetEditScene()->GetSceneObject<SpectatorCamera>("SpectatorCamera");
	if (!specCamera)return;
	GameObject* obj = specCamera->GetClickedObject();
	if (!obj)return;
	Text* text = obj->GetComponent<Text>();
	if (text)
	{
		// ===== �e�L�X�g�ɕ������� ===== //
		// �X�L�����R�[�h�𕶎���ɕϊ�
		wchar_t typeChar[256];
		int result = GetKeyNameTextW(keyCode << 16, typeChar, sizeof(typeChar) / sizeof(wchar_t));

		// �����Ƃ��Ĉ�����L�[�����͂��ꂽ
		if (result == 1)
		{
			// �V�t�g�L�[��������Ă��Ȃ��H
			if(KeyInput::GetKeyUp(LeftShift) && KeyInput::GetKeyUp(RightShift))
				// �啶�����������ɕϊ�
				std::transform(typeChar, typeChar + result, typeChar, toLower);

			// �o�b�t�@�T�C�Y�̎擾
			int bufferSize = WideCharToMultiByte(CP_UTF8, 0, std::wstring(typeChar).c_str(), -1, nullptr, 0, nullptr, nullptr);
			// �o�b�t�@�̊m��
			char* charBuffer = new char[bufferSize];
			// ���C�h�����񂩂�}���`�o�C�g������ɕϊ�
			WideCharToMultiByte(CP_UTF8, 0, std::wstring(typeChar).c_str(), -1, charBuffer, bufferSize, nullptr, nullptr);
			
			// �e�L�X�g�ɕ�����ǉ�
			text->AddText(charBuffer);
			return;
		}

		// ===== ���̑��e�L�X�g�֌W�̏��� ===== //
		switch (keyCode)
		{
			// �o�b�N�X�y�[�X�L�[�̓���
			case KeyName::BackSpace:
				text->DeleteText();	// �e�L�X�g�̖������폜
				break;
			// �X�y�[�X�L�[�̓���
			case KeyName::Space:
				text->AddText(" "); // �e�L�X�g�ɋ󔒕�����ǉ�
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
