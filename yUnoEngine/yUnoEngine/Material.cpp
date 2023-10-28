#include "Material.h"
#include "renderer.h"
#include <directxmath.h>

void PublicSystem::Material::Draw()
{
	MATERIAL Material;
	Material.Diffuse = Material_Color;	// �F�E���l��ݒ�
	Material.TextureEnable = true;
	Renderer::SetMaterial(Material);
}

void PublicSystem::Material::SetMateiralColor(PublicSystem::Color _colorParam)
{
	Material_Color = _colorParam;
}
