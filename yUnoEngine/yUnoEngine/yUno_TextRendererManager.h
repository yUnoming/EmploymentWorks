#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include <Shlwapi.h>
#include <vector>
#include "renderer.h"



namespace yUno_SystemManager
{
	// �e�L�X�g�`��ɕK�v�ȏ������s���N���X
	class yUno_TextRendererManager
	{
		private:
			// ----- variables / �ϐ� ----- //
			/// <summary>
			/// �쐬���ꂽ�t�H���g�Q </summary>
			static std::vector<HFONT> m_CreateFonts;

			// ���ݎg�p����t�H���g�̗v�f��
			static int m_Now_Font_Index;

		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			/// �t�H���g�e�N�X�`�����쐬���A�擾 </summary>
			/// <param name = "_chara">
			/// �`�悵�������� </param>
			static ID3D11Texture2D* Get_FontTexture(const char* _chara);

			/// <summary>
			/// �V�F�[�_�[���\�[�X�r���[���쐬���A�擾 </summary>
			/// <param name = "_fontTexture">
			/// �t�H���g�e�N�X�`���̃|�C���^�[ </param>
			static ID3D11ShaderResourceView* Get_ShaderResourceView(ID3D11Texture2D* _fontTexture);

			/// <summary>
			/// �쐬�����t�H���g���Z�b�g���� </summary>
			/// <param name = "_addFont">
			/// ����ǉ�����t�H���g	</param>
			static void Set_Font(HFONT _addFont);
	};
}

