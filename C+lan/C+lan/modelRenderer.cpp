
#define _CRT_SECURE_NO_WARNINGS
#include "SystemSceneManager.h"
#include "SystemNetWorkManager.h"

#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include <WICTextureLoader.h>
#include "Shader.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "Material.h"
#include "SceneManager.h"
#include "SpectatorCamera.h"

using namespace DirectX::SimpleMath;

std::unordered_map<std::string, MODEL*> ModelRenderer::m_ModelPool;
std::unordered_map<std::string, std::vector<VERTEX_3D>> ModelRenderer::m_verticesPool;

void Ctlan::PrivateSystem::ModelRenderer::Init()
{
	// マテリアルを取得
	m_material = GetComponent<Material>();
}

void ModelRenderer::Draw()
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Model->VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_Model->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	for( unsigned int i = 0; i < m_Model->SubsetNum; i++ )
	{
		// マテリアル設定
		m_Model->SubsetArray[i].Material.Material.Diffuse = m_material->materialColor;
		Renderer::SetMaterial(m_Model->SubsetArray[i].Material.Material);

		// テクスチャ設定
		if(m_Model->SubsetArray[i].Material.Texture)
			Renderer::GetDeviceContext()->PSSetShaderResources( 0, 1, &m_Model->SubsetArray[i].Material.Texture );

		// ポリゴン描画
		Renderer::GetDeviceContext()->DrawIndexed(m_Model->SubsetArray[i].IndexNum, m_Model->SubsetArray[i].StartIndex, 0 );
	}

// デバッグ時
#if _DEBUG
	// ===== 輪郭線の表示処理 ===== //
	// カメラ取得
	EngineObject::SpectatorCamera* spectatorCamera = (Ctlan::EngineObject::SpectatorCamera*)SystemManager::SystemSceneManager::GetEditScene()->GetSceneObject("SpectatorCamera");

	// このコンポーネントが追加されているオブジェクトがクリックされている？
	if (spectatorCamera && gameObject == spectatorCamera->GetClickedObject() ||
		SystemManager::SystemNetWorkManager::GetServer()->IsRockObject(gameObject->GetName()))
	{
		// ----- 輪郭線の表示処理 ----- //
		// シェーダー設定
		Shader shader;
		shader.Load("Assets\\Shaders\\OutlineVS.cso", "Assets\\Shaders\\OutlinePS.cso");
		// カリングモード切り替え
		Renderer::SetCullingMode(D3D11_CULL_FRONT);
		for (unsigned int i = 0; i < m_Model->SubsetNum; i++)
		{
			// マテリアル設定
			m_Model->SubsetArray[i].Material.Material.Diffuse = m_material->materialColor;
			Renderer::SetMaterial(m_Model->SubsetArray[i].Material.Material);

			// 定数バッファの作成
			ID3D11Buffer* constantBuffer{};
			DirectX::XMFLOAT4 color = Ctlan::PublicSystem::Color::GetColor((Ctlan::PublicSystem::Color::ColorType)SystemManager::SystemNetWorkManager::GetServer()->GetRockUserNo(gameObject->GetName()));
			CD3D11_BUFFER_DESC constantBufferDesc(sizeof(color), D3D11_BIND_CONSTANT_BUFFER);
			if (FAILED(Renderer::GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer))){}
			else
			{
				// バッファにデータをセット
				Renderer::GetDeviceContext()->UpdateSubresource(constantBuffer, 0, nullptr, &color, 0, 0);
				// シェーダーに定数バッファをセット
				Renderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &constantBuffer);
			}

			// テクスチャ設定
			if (m_Model->SubsetArray[i].Material.Texture)
				Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Model->SubsetArray[i].Material.Texture);

			// ポリゴン描画
			Renderer::GetDeviceContext()->DrawIndexed(m_Model->SubsetArray[i].IndexNum, m_Model->SubsetArray[i].StartIndex, 0);

			if (constantBuffer)
				constantBuffer->Release();
		}
		// カリングモード切り替え
		Renderer::SetCullingMode(D3D11_CULL_NONE);
	}
#endif
}

void ModelRenderer::Preload(const char *FileName)
{
	if (m_ModelPool.count(FileName) > 0)
	{
		return;
	}

	MODEL* model = new MODEL;
	LoadModel(FileName, model);

	m_ModelPool[FileName] = model;
	delete model;
}


void ModelRenderer::UnloadAll()
{
	for (std::pair<const std::string, MODEL*> pair : m_ModelPool)
	{
		pair.second->VertexBuffer->Release();
		pair.second->IndexBuffer->Release();

		for (unsigned int i = 0; i < pair.second->SubsetNum; i++)
		{
			if (pair.second->SubsetArray[i].Material.Texture)
				pair.second->SubsetArray[i].Material.Texture->Release();
		}

		delete[] pair.second->SubsetArray;

		delete pair.second;
	}

	m_ModelPool.clear();
}


void ModelRenderer::Load(const char *FileName)
{
	if (m_ModelPool.count(FileName) > 0)
	{
		m_Model = m_ModelPool[FileName];
		m_vertices = m_verticesPool[FileName];
		return;
	}

	m_Model = new MODEL;
	LoadModel(FileName, m_Model);

	m_ModelPool[FileName] = m_Model;
	m_verticesPool[FileName] = m_vertices;
}

void ModelRenderer::LoadModel( const char *FileName, MODEL *Model)
{

	MODEL_OBJ modelObj;
	LoadObj( FileName, &modelObj );



	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( VERTEX_3D ) * modelObj.VertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = modelObj.VertexArray;

		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &Model->VertexBuffer );
	}


	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( unsigned int ) * modelObj.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = modelObj.IndexArray;

		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &Model->IndexBuffer );
	}

	// サブセット設定
	{
		Model->SubsetArray = new SUBSET[ modelObj.SubsetNum ];
		Model->SubsetNum = modelObj.SubsetNum;

		for( unsigned int i = 0; i < modelObj.SubsetNum; i++ )
		{
			Model->SubsetArray[i].StartIndex = modelObj.SubsetArray[i].StartIndex;
			Model->SubsetArray[i].IndexNum = modelObj.SubsetArray[i].IndexNum;

			Model->SubsetArray[i].Material.Material = modelObj.SubsetArray[i].Material.Material;

			Model->SubsetArray[i].Material.Texture = nullptr;

			// s-jisをワイド文字に
			std::wstring ws = sjis_to_wide_winapi(modelObj.SubsetArray[i].Material.TextureName);

			// テクスチャ読み込み
			DirectX::CreateWICTextureFromFile(
				Renderer::GetDevice(),
				//				modelObj.SubsetArray[i].Material.TextureName,
				ws.c_str(),
				nullptr,
				&Model->SubsetArray[i].Material.Texture);

			if (Model->SubsetArray[i].Material.Texture)
				Model->SubsetArray[i].Material.Material.TextureEnable = true;
			else
				Model->SubsetArray[i].Material.Material.TextureEnable = false;

		}
	}

	delete[] modelObj.VertexArray;
	delete[] modelObj.IndexArray;
	delete[] modelObj.SubsetArray;

}






//モデル読込////////////////////////////////////////////
void ModelRenderer::LoadObj( const char *FileName, MODEL_OBJ *ModelObj )
{

	char dir[MAX_PATH];
	strcpy (dir, FileName );
	PathRemoveFileSpecA(dir);





	DirectX::SimpleMath::Vector3	*positionArray;
	DirectX::SimpleMath::Vector3	*normalArray;
	DirectX::SimpleMath::Vector2	*texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL	*materialArray = nullptr;
	unsigned int	materialNum = 0;

	char str[256]{};
	char *s;
	char c;


	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);



	//要素数カウント
	while( true )
	{
		fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "v" ) == 0 )
		{
			positionNum++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			normalNum++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			texcoordNum++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			subsetNum++;
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			in = 0;

			do
			{
				fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));
				vertexNum++;
				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c!= '\r' );

			//四角は三角に分割
			if( in == 4 )
				in = 6;

			indexNum += in;
		}
	}


	//メモリ確保
	positionArray = new DirectX::SimpleMath::Vector3[ positionNum ];
	normalArray = new DirectX::SimpleMath::Vector3[ normalNum ];
	texcoordArray = new DirectX::SimpleMath::Vector2[ texcoordNum ];


	ModelObj->VertexArray = new VERTEX_3D[ vertexNum ];
	ModelObj->VertexNum = vertexNum;

	ModelObj->IndexArray = new unsigned int[ indexNum ];
	ModelObj->IndexNum = indexNum;

	ModelObj->SubsetArray = new SUBSET[ subsetNum ];
	ModelObj->SubsetNum = subsetNum;




	//要素読込
	DirectX::SimpleMath::Vector3 *position = positionArray;
	DirectX::SimpleMath::Vector3	*normal = normalArray;
	DirectX::SimpleMath::Vector2	*texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;


	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "mtllib" ) == 0 )
		{
			//マテリアルファイル
			fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			LoadMaterial( path, &materialArray, &materialNum );
		}
		else if( strcmp( str, "o" ) == 0 )
		{
			//オブジェクト名
			fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));
		}
		else if( strcmp( str, "v" ) == 0 )
		{
			//頂点座標
			fscanf_s( file, "%f", &position->x );
			fscanf_s( file, "%f", &position->y );
			fscanf_s( file, "%f", &position->z );
			position++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			//法線
			fscanf_s( file, "%f", &normal->x );
			fscanf_s( file, "%f", &normal->y );
			fscanf_s( file, "%f", &normal->z );
			normal++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			//テクスチャ座標
			fscanf_s( file, "%f", &texcoord->x );
			fscanf_s( file, "%f", &texcoord->y );
			texcoord->x = 1.0f - texcoord->x;
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			//マテリアル
			fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

			if( sc != 0 )
				ModelObj->SubsetArray[ sc - 1 ].IndexNum = ic - ModelObj->SubsetArray[ sc - 1 ].StartIndex;

			ModelObj->SubsetArray[ sc ].StartIndex = ic;


			for( unsigned int i = 0; i < materialNum; i++ )
			{
				if( strcmp( str, materialArray[i].Name ) == 0 )
				{
					ModelObj->SubsetArray[ sc ].Material.Material = materialArray[i].Material;
					strcpy( ModelObj->SubsetArray[ sc ].Material.TextureName, materialArray[i].TextureName );
					strcpy( ModelObj->SubsetArray[ sc ].Material.Name, materialArray[i].Name );

					break;
				}
			}

			sc++;
			
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			//面
			in = 0;
			VERTEX_3D vertex;

			do
			{
				fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

				s = strtok( str, "/" );	
				ModelObj->VertexArray[vc].Position = positionArray[ atoi( s ) - 1 ];
				vertex.Position = positionArray[atoi(s) - 1];

				if( s[ strlen( s ) + 1 ] != '/' )
				{
					//テクスチャ座標が存在しない場合もある
					s = strtok( nullptr, "/" );
					ModelObj->VertexArray[vc].TexCoord = texcoordArray[ atoi( s ) - 1 ];
					vertex.TexCoord = texcoordArray[atoi(s) - 1];
				}
				s = strtok( nullptr, "/" );	
				ModelObj->VertexArray[vc].Normal = normalArray[ atoi( s ) - 1 ];
				vertex.Normal = normalArray[atoi(s) - 1];

				ModelObj->VertexArray[vc].Diffuse = DirectX::SimpleMath::Color( 1.0f, 1.0f, 1.0f, 1.0f );
				vertex.Diffuse = DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f);

				m_vertices.push_back(vertex);
				ModelObj->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c != '\r' );

			//四角は三角に分割
			if( in == 4 )
			{
				ModelObj->IndexArray[ic] = vc - 4;
				ic++;
				ModelObj->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if( sc != 0 )
		ModelObj->SubsetArray[ sc - 1 ].IndexNum = ic - ModelObj->SubsetArray[ sc - 1 ].StartIndex;


	fclose( file );


	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}

//マテリアル読み込み///////////////////////////////////////////////////////////////////
void ModelRenderer::LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum )
{

	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpecA(dir);



	char str[256]{};

	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);

	MODEL_MATERIAL *materialArray;
	unsigned int materialNum = 0;

	//要素数カウント
	while( true )
	{
		fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			materialNum++;
		}
	}


	//メモリ確保
	materialArray = new MODEL_MATERIAL[ materialNum ];


	//要素読込
	int mc = -1;

	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			mc++;
			//マテリアル名
			fscanf_s( file, "%s", &materialArray[mc].Name, static_cast<unsigned int>(sizeof(materialArray[mc].Name) / sizeof(materialArray[mc].Name[0])));
			strcpy_s( materialArray[mc].TextureName, "" );

			materialArray[mc].Material.Emission.x = 0.0f;
			materialArray[mc].Material.Emission.y = 0.0f;
			materialArray[mc].Material.Emission.z = 0.0f;
			materialArray[mc].Material.Emission.w = 0.0f;
		}
		else if( strcmp( str, "Ka" ) == 0 )
		{
			//アンビエント
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Ambient.x );
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Ambient.y );
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Ambient.z );
			materialArray[ mc ].Material.Ambient.w = 1.0f;
		}
		else if( strcmp( str, "Kd" ) == 0 )
		{
			//ディフューズ
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Diffuse.x );
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Diffuse.y );
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Diffuse.z );
			materialArray[ mc ].Material.Diffuse.w = 1.0f;
		}
		else if( strcmp( str, "Ks" ) == 0 )
		{
			//スペキュラ
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Specular.x );
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Specular.y );
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Specular.z );
			materialArray[ mc ].Material.Specular.w = 1.0f;
		}
		else if( strcmp( str, "Ns" ) == 0 )
		{
			//スペキュラ強度
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Shininess );
		}
		else if( strcmp( str, "d" ) == 0 )
		{
			//アルファ
			fscanf_s( file, "%f", &materialArray[ mc ].Material.Diffuse.w );
		}
		else if( strcmp( str, "map_Kd" ) == 0 )
		{
			//テクスチャ
			fscanf_s( file, "%s", str, static_cast<unsigned int>(sizeof(str)));

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			strcat( materialArray[ mc ].TextureName, path );
		}
	}

	fclose(file);

	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}

