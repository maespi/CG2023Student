//
//  Material.hpp
//  ComputerGraphics
//
//  Created by Sergi Puig i Bertol on 19/3/23.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include "shader.h"
#include "texture.h"
#include "image.h"

class Material
{
public:
    Shader shader;
    Texture texture;
    Vector3 color_comp;
    float shininess;
    
};

#endif /* Material_hpp */
