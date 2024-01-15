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
#include "TextRenderer.h"


namespace yUno_SystemManager
{
	/// <summary>
	/// �e�L�X�g�`����s�����߂̏������Ǘ�����N���X	</summary>
	class yUno_TextRendererManager
	{
		private:
			// ----- structs / �z�� ----- //
			/// <summary>
			///	�t�H���g�e�N�X�`�����	</summary>
			struct FontTextureData
			{
				/// <summary>
				///	�쐬�����t�H���g�e�N�X�`���̕���	</summary>
				char fontText;
				/// <summary>
				///	�t�H���g�e�N�X�`��	</summary>
				ID3D11Texture2D* fontTexture;
			};


			// ----- variables / �ϐ� ----- //
			/// <summary>
			/// �쐬�����t�H���g�z�� </summary>
			static std::vector<HFONT> m_createFonts;
			/// <summary>
			/// �쐬�����t�H���g�e�N�X�`���z�� </summary>
			static std::vector<FontTextureData> m_fontTextureDatas;

			// ���ݎg�p����t�H���g�̗v�f��
			static int m_nowFontIndex;

			// ----- functions / �֐� ----- //
			/// <summary>
			///	�t�H���g�e�N�X�`�������ɍ쐬���Ă��邩�m�F	</summary>
			/// <param name="text">
			///	�������镶��	</param>
			/// <returns>
			/// �쐬�ς݂̃t�H���g�e�N�X�`���A�쐬���Ă��Ȃ����nullptr</returns>
			static ID3D11Texture2D* CheckFontTexture(char text);

		public:
			// ----- functions / �֐� ----- //
			/// <summary>
			/// �t�H���g�e�N�X�`�����쐬���A�擾 </summary>
			/// <param name = "text">
			/// �`�悷��e�L�X�g </param>
			/// <param name="textNum">
			/// �������ڂ�	</param>
			/// <returns>
			/// �쐬�����t�H���g�e�N�X�`��	</returns>
			static ID3D11Texture2D* GetFontTexture(char text, int textNum);

			/// <summary>
			/// �V�F�[�_�[���\�[�X�r���[���쐬���A�擾 </summary>
			/// <param name = "fontTexture">
			/// �t�H���g�e�N�X�`���̃|�C���^�[ </param>
			/// <returns>
			/// �쐬�����V�F�[�_�[���\�[�X�r���[	</returns>
			static ID3D11ShaderResourceView* GetShaderResourceView(ID3D11Texture2D* fontTexture);

			/// <summary>
			///	���_�o�b�t�@���쐬���A�擾	</summary>
			/// <param name="textData">
			///	�e�L�X�g���	</param>
			/// <param name="fontNum">
			///	�������ڂ��i�l��0 = �ꕶ���ځj	</param>
			/// <returns>
			/// �쐬�������_�o�b�t�@	</returns>
			static ID3D11Buffer* GetVertexBuffer(TextRenderer textData, int fontNum);

			/// <summary>
			/// �쐬�����t�H���g���Z�b�g </summary>
			/// <param name = "_addFont">
			/// ����ǉ�����t�H���g	</param>
			static void SetFont(HFONT addFont);
	};
}

