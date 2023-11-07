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


/// <summary>
///	�e�L�X�g�`��̏������s���N���X	</summary>
class TextRenderer : public EachFunction
{
	private:
		// ----- variables / �ϐ� ----- //
		/// <summary>
		/// �g�p����t�H���g�̃e�N�X�`��	</summary>
		ID3D11Texture2D* m_fontTexture{};
		/// <summary>
		/// �T���v���[�̏��	</summary>
		ID3D11SamplerState* m_samplerState{};
		/// <summary>
		/// �V�F�[�_�[���A�N�Z�X�ł���T�u���\�[�X	</summary>
		ID3D11ShaderResourceView* m_shaderResourceView{};
		/// <summary>
		/// ���_�o�b�t�@ </summary>
		ID3D11Buffer* m_vertexBuffer{};

		/// <summary>
		/// �O��\������Ă����e�L�X�g </summary>
		const char* m_lateText;

	public:
		//  ----- variables / �ϐ� ----- //
		/// <summary>
		/// �\������e�L�X�g </summary>
		const char* text;

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
		/// �`�悷��e�L�X�g���쐬���� </summary>
		/// <param name="text">
		///	�`�悵����������	</param>
		void CreateText(const char* text);
};

