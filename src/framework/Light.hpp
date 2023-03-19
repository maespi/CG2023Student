//
//  Light.hpp
//  ComputerGraphics
//
//  Created by Sergi Puig i Bertol on 19/3/23.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include "shader.h"
#include "texture.h"
#include "image.h"

class Light
{
    Vector3 position; //{x,y,z}
    Vector2 intensity; //{Id, Is}
};

#endif /* Light_hpp */
