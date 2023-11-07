#include "Material.h"
#include "renderer.h"
#include <directxmath.h>

void PublicSystem::Material::Draw()
{
	MATERIAL Material;
	Material.Diffuse = materialColor;	// FEƒ¿’l‚ğİ’è
	Material.TextureEnable = true;
	Renderer::SetMaterial(Material);
}

void PublicSystem::Material::SetMaterialColor(PublicSystem::Color colorParam)
{
	materialColor = colorParam;
}
