#include "entity.h"
#include "mesh.h"
#include "framework.h"
#include <iostream>




Entity::Entity() {
	mesh = new Mesh();
    model.SetIdentity();
	rMode = eRenderMode::WIREFRAME;
}

Entity::Entity(Mesh * m) {
	mesh = m;
    model.SetIdentity();
	rMode = eRenderMode::WIREFRAME;
}

Entity::Entity(const char* dir) {
	mesh = new Mesh();
	mesh->LoadOBJ(dir);
    model.SetIdentity();
	rMode = eRenderMode::WIREFRAME;
}

//Destructor
Entity::~Entity() {
}

//Render function to render mesh object
void Entity::Render(Image* framebuffer, Camera* camera, const Color& c, FloatImage* zBuffer, int type, Image* texture) {
    
   
    if (type == NORMAL_REND_TYPE){
        std::vector<Vector3> vertices = mesh->GetVertices();

        for (int i = 0; i < (vertices.size()-3); i+=3) {
            Vector3 v1 = vertices[i];
            Vector3 v2 = vertices[i+1];
            Vector3 v3 = vertices[i+2];

            //Transforma local to World
            v1 = model * v1;
            v2 = model * v2;
            v3 = model * v3;

            //World Space to Clip Space
            //Calculates if z is outside the camera
            bool negZ1;
            bool negZ2;
            bool negZ3;
            v1 = camera->ProjectVector(v1, negZ1);
            v2 = camera->ProjectVector(v2, negZ2);
            v3 = camera->ProjectVector(v3, negZ3);

            //Convert clip space positions to screen space
            if (!negZ1 && !negZ2 && !negZ3) {

                v1.x = (v1.x+1) / 2 * (framebuffer->width - 1);
                v1.y = (v1.y+1) / 2 * (framebuffer->height - 1);

                v2.x = (v2.x+1) / 2 * (framebuffer->width - 1);
                v2.y = (v2.y+1) / 2 * (framebuffer->height - 1);

                v3.x = (v3.x+1) / 2 * (framebuffer->width - 1);
                v3.y = (v3.y+1) / 2 * (framebuffer->height - 1);

                //Draw into space
                if (rMode == eRenderMode::TRIANGLES) {
                    framebuffer->DrawTriangle(v1.GetVector2(), v2.GetVector2(), v3.GetVector2(), c);
                }
                else if (rMode == eRenderMode::WIREFRAME) {//rMode == eRenderMode::WIREFRAME
                    framebuffer->DrawLineBresenham(v1.x, v1.y, v2.x, v2.y, c);
                    framebuffer->DrawLineBresenham(v2.x, v2.y, v3.x, v3.y, c);
                    framebuffer->DrawLineBresenham(v3.x, v3.y, v1.x, v1.y, c);
                    
                }else if (rMode == eRenderMode::TRIANGLES_INTERPOLATED){
                    std::vector<Vector2> uvs = mesh->GetUVs();
                    framebuffer->DrawTriangleInterpolated(v1, v2, v3, Color::RED, Color::BLUE, Color::GREEN,zBuffer,texture,uvs[i],uvs[i+1],uvs[1+2]);
                    
                }
                
            }
        }
    }else if (type == ZBUFFER_REND_TYPE){
        //init zBuffer
        for (int i = 0; i < zBuffer->width; i++) {
            for (int j = 0; j < zBuffer->height; j++) {
                zBuffer->SetPixel(i, j, std::numeric_limits<float>::max());
                //std::cout<< i+"\n" ;
            }
        }
         
        
        std::vector<Vector3> vertices = mesh->GetVertices();

        for (int i = 0; i < (vertices.size()-3); i+=3) {
            Vector3 v1 = vertices[i];
            Vector3 v2 = vertices[i+1];
            Vector3 v3 = vertices[i+2];
            

            //Transforma local to World
            v1 = model * v1;
            v2 = model * v2;
            v3 = model * v3;

            //World Space to Clip Space
            //Calculates if z is outside the camera
            bool negZ1;
            bool negZ2;
            bool negZ3;
            v1 = camera->ProjectVector(v1, negZ1);
            v2 = camera->ProjectVector(v2, negZ2);
            v3 = camera->ProjectVector(v3, negZ3);

            //Convert clip space positions to screen space
            if (!negZ1 && !negZ2 && !negZ3) {

                v1.x = (v1.x+1) / 2 * (framebuffer->width - 1);
                v1.y = (v1.y+1) / 2 * (framebuffer->height - 1);

                v2.x = (v2.x+1) / 2 * (framebuffer->width - 1);
                v2.y = (v2.y+1) / 2 * (framebuffer->height - 1);

                v3.x = (v3.x+1) / 2 * (framebuffer->width - 1);
                v3.y = (v3.y+1) / 2 * (framebuffer->height - 1);

                //Draw into space
                if (rMode == eRenderMode::TRIANGLES) {
                    framebuffer->DrawTriangle(v1.GetVector2(), v2.GetVector2(), v3.GetVector2(), c);
                }
                else if (rMode == eRenderMode::WIREFRAME) {
                    framebuffer->DrawLineBresenham(v1.x, v1.y, v2.x, v2.y, c);
                    framebuffer->DrawLineBresenham(v2.x, v2.y, v3.x, v3.y, c);
                    framebuffer->DrawLineBresenham(v3.x, v3.y, v1.x, v1.y, c);
                    
                }else if (rMode == eRenderMode::TRIANGLES_INTERPOLATED){
                    std::vector<Vector2> uvs = mesh->GetUVs();
                    framebuffer->DrawTriangleInterpolated(v1, v2, v3, Color::RED, Color::BLUE, Color::GREEN, zBuffer,texture,uvs[i],uvs[i+1],uvs[1+2]);
                    
                }
                
            }
        }
    }
    
	
}

void Entity::Update(float sec, int type){
	
    if (type == 1){//vermella
        
        model.Translate(-sec/15,0,0);
        
    } else if (type == 2){//blava
        model.Rotate(sec, Vector3(0,sec,2));

    } else if(type == 3){//blanca
        float c = std::fmod(sec, 180);
        
        model.M[0][0] = model.M[0][0] * cos(c);
        model.M[0][2] = model.M[0][2] * -sin(c);
        model.M[2][0] = model.M[2][0] * sin(c);
        model.M[2][2] = model.M[2][2] * cos(c);
        model.Rotate(sec, Vector3(model.M[0][0], model.M[1][0], model.M[2][0]));

    }
}


