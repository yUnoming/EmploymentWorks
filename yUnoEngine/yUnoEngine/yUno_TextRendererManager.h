#pragma once
/**
* @file		yUno_TextRendererManager.h
* @brief	yUno_TextRendererManager�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.07
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <Shlwapi.h>
#include <vector>
#include "renderer.h"


namespace yUno_SystemManager
{
	/// <summary>
	/// �e�L�X�g�`����s�����߂̏������Ǘ�����N���X	</summary>
	class yUno_TextRendererManager
	{
		private:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			/// �쐬���ꂽ�t�H���g�Q </summary>
			static std::vector<HFONT> m_createFonts;

			// ���ݎg�p����t�H���g�̗v�f��
			static int m_nowFontIndex;

		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			/// �t�H���g�e�N�X�`�����쐬���A�擾 </summary>
			/// <param name = "text">
			/// �`�悵�������� </param>
			static ID3D11Texture2D* GetFontTexture(const char* text);

			/// <summary>
			/// �V�F�[�_�[���\�[�X�r���[���쐬���A�擾 </summary>
			/// <param name = "fontTexture">
			/// �t�H���g�e�N�X�`���̃|�C���^�[ </param>
			static ID3D11ShaderResourceView* GetShaderResourceView(ID3D11Texture2D* fontTexture);

			/// <summary>
			/// �쐬�����t�H���g���Z�b�g���� </summary>
			/// <param name = "_addFont">
			/// ����ǉ�����t�H���g	</param>
			static void SetFont(HFONT addFont);
	};
}

