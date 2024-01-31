#pragma once
/**
* @file		TextRenderer.h
* @brief	TextRenderer�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.01
*/
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "renderer.h"

#include <vector>

namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	�e�L�X�g�`��̏������s���N���X	</summary>
		class TextRenderer : public EachFunction
		{
			private:
				// ----- structs / �\���� ----- //
				/// <summary>
				///	�e�L�X�g���	</summary>
				struct TextInfo
				{
					/// <summary>
					/// �g�p����t�H���g�̃e�N�X�`��	</summary>
					ID3D11Texture2D* fontTexture;
					/// <summary>
					///	�V�F�[�_�[���A�N�Z�X�ł���T�u���\�[�X	</summary>
					ID3D11ShaderResourceView* shaderResourceView;
				};


				// ----- variables / �ϐ� ----- //
				/// <summary>
				///	�e�L�X�g��񃊃X�g	</summary>
				std::vector<TextInfo> m_TextInfoList;
				/// <summary>
				/// �T���v���[�̏��	</summary>
				ID3D11SamplerState* m_samplerState{};

				/// <summary>
				/// �O��\������Ă����e�L�X�g </summary>
				char m_lateText[101]{};

				/// <summary>
				///	�e�L�X�g�̒����i�������j	</summary>
				int m_textLength = 0;

				// ----- functions / �֐� ----- //
				/// <summary>
				/// �`�悷��e�L�X�g���쐬 </summary>
				/// <param name="text">
				///	�`�悷�镶��	</param>
				/// <param name="textNum">
				/// �������ڂ�	</param>
				/// <returns>
				/// �쐬�����e�L�X�g���	</returns>
				TextInfo CreateText(char text, int textNum);

				/// <summary>
				///	�`�悷��e�L�X�g���쐬�i���_�o�b�t�@�͍쐬���Ȃ��j	</summary>
				/// <param name="text"> 
				///	�`�悷�镶��	</param>
				/// <param name="textNum">
				/// �������ڂ�	</param>ee
				/// <returns>
				/// �쐬�����e�L�X�g���	</returns>
				TextInfo CreateTextWithoutVertexBuffer(char text, int textNum);

			public:
				//  ----- variables / �ϐ� ----- //
				/// <summary>
				/// �\������e�L�X�g </summary>
				const char* text = "";
				/// <summary>
				///	�e�L�X�g�̓��e�ύX�ȂǂŎg�����e�L�X�g	</summary>
				char dummyText[101] = {};
				/// <summary>
				/// �����T�C�Y </summary>
				Vector2 fontSize;
				/// <summary>
				///	�e�L�X�g�̍��㒸�_�ʒu	</summary>
				Vector2 leftTopPoint = Vector2(0.f, 0.f);

				// ----- functions / �֐� ----- //
				/// <summary>
				///	������	</summary>
				void Init();
				/// <summary>
				///	�X�V	</summary>
				void Update();
				/// <summary>
				///	�`��	</summary>
				void Draw();

				/// <summary>
				///	�e�L�X�g�̒����i�������j���擾	</summary>
				int GetTextLength() { return m_textLength; };
		};
	}
}