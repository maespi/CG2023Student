//
//  Material.h
//  ComputerGraphics
//
//  Created by Sergi Puig i Bertol on 19/3/23.
//

#include <stdio.h>
#include "shader.h"
#include "texture.h"
#include "image.h"
#include "light.h"

class Material
{
private:
    struct sLight
    {
        Light light;
    };
public:
    struct sUniformData
    {
        Matrix44 modelMatrix;
        Matrix44 vpMatrix;
        float intensity;
        sLight sceneLight1;
        sLight sceneLight2;
    };

    Shader shader;
    Texture texture;
    Vector3 color_comp;
    float shininess;

    //3.1 Creation of new classes
    void Dissable();
    void Enable(const sUniformData& uniformData);
    void Enable();

    Material();

    //Getters & Setters
    void setShader(Shader s) { shader = s; }
    Shader getShader() { return shader; }
    void setTexture(Texture t) { texture = t; }
    Texture getTexture() { return texture; }
    void setColor_comp(Vector3 c) { color_comp = c; }
    Vector3 getColor_comp() { return color_comp; }
    void setShininess(float s) { shininess = s; }
    float getShininness() { return shininess; }
    
};
