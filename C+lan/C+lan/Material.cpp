#include "Material.h"
#include "renderer.h"
#include <directxmath.h>

void Ctlan::PublicSystem::Material::Draw()
{
	MATERIAL Material;
	Material.Diffuse = materialColor;	// �F�E���l��ݒ�
	Material.TextureEnable = true;
	Renderer::SetMaterial(Material);
}

void Ctlan::PublicSystem::Material::SetMaterialColor(Ctlan::PublicSystem::Color colorParam)
{
	materialColor = colorParam;
}
