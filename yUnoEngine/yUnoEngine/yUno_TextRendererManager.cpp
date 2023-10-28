// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "yUno_TextRendererManager.h"
#include "renderer.h"
#include <d3d11.h>
#include <iostream>


// ������������������������������ //
// �@�@static�����o�ϐ��̒�`�@�@ //
// ������������������������������ //
std::vector<HFONT> yUno_SystemManager::yUno_TextRendererManager::m_CreateFonts;
int yUno_SystemManager::yUno_TextRendererManager::m_Now_Font_Index;



ID3D11Texture2D* yUno_SystemManager::yUno_TextRendererManager::Get_FontTexture(const char* _chara)
{
	// ===== ���݂̃E�B���h�E�Ƀt�H���g��K�p ===== //
	// �f�o�C�X�R���e�L�X�g�擾
	HDC hdc = GetDC(NULL);
	// �t�H���g�擾
	HFONT oldFont = (HFONT)SelectObject(hdc, m_CreateFonts[m_Now_Font_Index]);

	// �e�N�X�`���ɏ������ޕ������Z�b�g
	UINT code = (UINT)*_chara;

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
	DeleteObject(m_CreateFonts[m_Now_Font_Index]);
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

	// �e�N�X�`��2D�ϐ�
	ID3D11Texture2D* Texture2D;

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
	return Texture2D;
}

ID3D11ShaderResourceView* yUno_SystemManager::yUno_TextRendererManager::Get_ShaderResourceView(ID3D11Texture2D* _fontTexture)
{
	// �V�F�[�_�[���\�[�X�r���[�̏���ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// �V�F�[�_�[���\�[�X�r���[�ϐ�
	ID3D11ShaderResourceView* Shader_Resource_View;

	// �V�F�[�_�[���\�[�X�r���[�̍쐬
	HRESULT hr = Renderer::GetDevice()->CreateShaderResourceView(_fontTexture, &srvDesc, &Shader_Resource_View);

	// �V�F�[�_�[���\�[�X�r���[�̍쐬�Ɏ��s�����H
	if (hr != S_OK)
	{
		std::cout << "CreateShaderResourceView() Failed!!! ErrorCode�F" << GetLastError() << std::endl;	// �G���[���O�\��
		return NULL;
	}

	return Shader_Resource_View;
}

void yUno_SystemManager::yUno_TextRendererManager::Set_Font(HFONT _addFont)
{
	// �����Ŏ󂯎�����t�H���g��ǉ�����
	m_CreateFonts.push_back(_addFont);
}
