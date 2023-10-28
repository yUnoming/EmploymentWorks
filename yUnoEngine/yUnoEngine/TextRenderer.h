#pragma once
// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "renderer.h"


// �e�L�X�g��`�悷�邽�߂̃N���X
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
		const char* m_text;

		// ----- functions / �֐� ----- //
		void Init();
		void Update();
		void Draw();

		/// <summary>
		/// �`�悷��e�L�X�g���쐬���� </summary>
		void Create_Text(const char* _text);
};

