#pragma once
/**
* @file		Component.h
* @brief	Component�N���X�̃w�b�_�[�t�@�C��
* @author	Kojima, Kosei
* @date		2023.11.27
*/

// ������������������������������ //
// �@�@�t�@�C���̃C���N���[�h�@�@ //
// ������������������������������ //
#include "EachFunction.h"
#include "renderer.h"

namespace Ctlan
{
	namespace PublicSystem
	{
		/// <summary>
		///	�V�F�[�_�[��\���N���X	</summary>
		class Shader : public EachFunction
		{
			private:
				// ----- variables / �ϐ� ----- //
				/// <summary>
				///	���_�V�F�[�_�[	</summary>
				ID3D11VertexShader* m_vertexShader{};
				/// <summary>
				///	�s�N�Z���V�F�[�_�[	</summary>
				ID3D11PixelShader* m_pixelShader{};
				/// <summary>
				///	���_���C�A�E�g	</summary>
				ID3D11InputLayout* m_vertexLayout{};

			public:
				// ----- functions / �֐� ----- //
				/// <summary>
				/// �I��		</summary>
				void Uninit() override;
				/// <summary>
				/// �`��		</summary>
				void Draw() override;

				/// <summary>
				///	�V�F�[�_�[��ǂݍ���	</summary>
				/// <param name="vertexShader">
				///	���_�V�F�[�_�[�̃t�@�C���p�X	</param>
				/// <param name="pixelShader">
				///	�s�N�Z���V�F�[�_�[�̃t�@�C���p�X	</param>
				void Load(const char* vertexShader, const char* pixelShader);
		};
	}
}