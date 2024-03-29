#pragma once
//
//
// 授業サンプルから取得したファイルです。
// 変更、修正している箇所はありますが、
// 私が０から作成したものではございません。
//
//
#include	<d3d11.h>
#include	<SimpleMath.h>
#include	"Application.h"

// リンクすべき外部ライブラリ
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"d3d11.lib")

// ３Ｄ頂点データ
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 Position;
	DirectX::SimpleMath::Vector3 Normal;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Vector2 TexCoord;
};


// マテリアル
struct MATERIAL
{
	DirectX::XMFLOAT4	Ambient = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT4	Diffuse = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT4	Specular = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT4	Emission = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	float		Shininess = 0;
	BOOL		TextureEnable = false;
	float		Dummy[2]{};
};


// 平行光源
struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];
	DirectX::SimpleMath::Vector4	Direction;
	DirectX::SimpleMath::Color	Diffuse;
	DirectX::SimpleMath::Color	Ambient;
};


namespace Ctlan
{
	namespace PrivateSystem
	{
		/// <summary>
		///	レンダラー	</summary>
		class Renderer
		{
		private:

			static D3D_FEATURE_LEVEL       m_FeatureLevel;

			static ID3D11Device* m_Device;
			static ID3D11DeviceContext* m_DeviceContext;
			static IDXGISwapChain* m_SwapChain;
			static ID3D11RenderTargetView* m_RenderTargetView;
			static ID3D11DepthStencilView* m_DepthStencilView;
			static ID3D11RasterizerState* m_rasterizerState[3];

			static ID3D11Buffer* m_WorldBuffer;
			static ID3D11Buffer* m_ViewBuffer;
			static ID3D11Buffer* m_ProjectionBuffer;
			static ID3D11Buffer* m_MaterialBuffer;
			static ID3D11Buffer* m_LightBuffer;


			static ID3D11DepthStencilState* m_DepthStateEnable;
			static ID3D11DepthStencilState* m_DepthStateDisable;

			static ID3D11BlendState* m_BlendState;
			static ID3D11BlendState* m_BlendStateATC;

			static Application* m_Application;


		public:
			static void Init(Application* ap);
			static void Uninit();
			static void Begin();
			static void End();

			static void SetDepthEnable(bool Enable);
			static void SetATCEnable(bool Enable);
			static void SetWorldViewProjection2D();
			static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);
			static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);
			static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);
			static void SetMaterial(MATERIAL Material);
			static void SetLight(LIGHT Light);
			static void SetCullingMode(D3D11_CULL_MODE cullMode);

			static ID3D11Device* GetDevice(void) { return m_Device; }
			static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }

			static void ClearDepthStencilView() {
				m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			}

			static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
			static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);


		};
	}
}
