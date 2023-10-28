#include "Material.h"
#include "renderer.h"
#include <directxmath.h>

void PublicSystem::Material::Draw()
{
	MATERIAL Material;
	Material.Diffuse = Material_Color;	// FEƒ¿’l‚ğİ’è
	Material.TextureEnable = true;
	Renderer::SetMaterial(Material);
}

void PublicSystem::Material::SetMateiralColor(PublicSystem::Color _colorParam)
{
	Material_Color = _colorParam;
}
