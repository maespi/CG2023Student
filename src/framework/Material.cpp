//
//  Material.cpp
//  ComputerGraphics
//
//  Created by Sergi Puig i Bertol on 19/3/23.
//

#include "material.h"


Material::Material()
{
}

void Material::Dissable()
{
	shader.Disable();
}

void Material::Enable(const sUniformData& uniformData)
{
	shader.Enable();
}
