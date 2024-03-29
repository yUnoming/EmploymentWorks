#include "Material.h"
#include "renderer.h"
#include <directxmath.h>

void Ctlan::PublicSystem::Material::Draw()
{
	MATERIAL Material;
	Material.Diffuse = materialColor;	// 色・α値を設定
	Material.TextureEnable = true;
	Renderer::SetMaterial(Material);
}

void Ctlan::PublicSystem::Material::SetMaterialColor(Ctlan::PublicSystem::Color colorParam)
{
	materialColor = colorParam;
}
