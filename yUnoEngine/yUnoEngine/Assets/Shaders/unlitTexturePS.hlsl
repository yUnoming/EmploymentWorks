
#include "common.hlsl"


Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);


float4 main(PS_IN In) : SV_Target
{
    float4 outDiffuse = (1.0f, 1.0f, 1.0f, 1.0f);
    if (Material.TextureEnable)
    {
        outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
        outDiffuse *= In.Diffuse * Material.Diffuse;
    }
    else
    {
        outDiffuse = In.Diffuse * Material.Diffuse;
    }
    return outDiffuse;
}
