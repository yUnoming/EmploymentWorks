#pragma once
//
//
// ���ƃT���v������擾�����t�@�C���ł��B
// �ύX�A�C�����Ă���ӏ��͂���܂����A
// �����O����쐬�������̂ł͂������܂���B
//
//
#include <string>
#include <unordered_map>
#include "EachFunction.h"
#include "Material.h"
#include "utftosjisconv.h"
#include "renderer.h"

// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256]{};
	MATERIAL					Material;
	char						TextureName[256]{};
	ID3D11ShaderResourceView*	Texture = nullptr;
};


// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex = 0;
	unsigned int	IndexNum = 0;
	MODEL_MATERIAL	Material = MODEL_MATERIAL();
};


// ���f���\����
struct MODEL_OBJ
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};

struct MODEL
{
	ID3D11Buffer*	VertexBuffer;
	ID3D11Buffer*	IndexBuffer;

	SUBSET*			SubsetArray;
	unsigned int	SubsetNum;
};

namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	���f���`����s���N���X	</summary>
		class ModelRenderer : public EachFunction
		{
			private:

				static std::unordered_map<std::string, MODEL*> m_ModelPool;
				static std::unordered_map<std::string, std::vector<VERTEX_3D>> m_verticesPool;

				void LoadModel(const char* FileName, MODEL* Model);
				void LoadObj(const char* FileName, MODEL_OBJ* ModelObj);
				void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);

				std::vector<VERTEX_3D> m_vertices;

				MODEL* m_Model{};
				Material* m_material{};

			public:

				void Preload(const char* FileName);
				static void UnloadAll();

				void Load(const char* FileName);

				void Init() override;
				void Draw() override;

				std::vector<VERTEX_3D> GetModelVertices() { return m_vertices; };
		};
	}
}