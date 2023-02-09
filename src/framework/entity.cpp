#include "entity.h"
#include "mesh.h"
#include "framework.h"

Entity::Entity() {
	mesh = new Mesh();
    model.SetIdentity();
}

Entity::Entity(Mesh * m) {
	mesh = m;
    model.SetIdentity();
}

Entity::Entity(const char* dir) {
	mesh = new Mesh();
	mesh->LoadOBJ(dir);
    model.SetIdentity();
}

//Destructor
Entity::~Entity() {
}

//Render function to render mesh object
void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    
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

			v1.x = v1.x * (framebuffer->width - 1);
			v1.y = v1.y * (framebuffer->height - 1);

			v2.x = v2.x * (framebuffer->width - 1);
			v2.y = v2.y * (framebuffer->height - 1);

			v3.x = v3.x * (framebuffer->width - 1);
			v3.y = v3.y * (framebuffer->height - 1);

			//Set Line Bresenham to buffer
			framebuffer->DrawLineBresenham(v1.x, v1.y, v2.x, v2.y, c);
			framebuffer->DrawLineBresenham(v2.x, v2.y, v3.x, v3.y, c);
			framebuffer->DrawLineBresenham(v3.x, v3.y, v1.x, v1.y, c);
		}
		
	}
}

void Entity::Update(float sec)
{
	float c = std::fmod(sec, 180);
	model.M[0][0] = model.M[0][0] * cos(c);
	model.M[0][2] = model.M[0][2] * -sin(c);
	model.M[2][0] = model.M[2][0] * sin(c);
	model.M[2][2] = model.M[2][2] * cos(c);


    
    for (int i = 0;i<1000;i++){
        model.Rotate(sec/93, Vector3(model.M[0][0], model.M[1][0], model.M[2][0]));
        model.Scale(sec*100);
    }
    
    for (int i = 0;i<1000;i++){
        model.Rotate(-sec/93, Vector3(model.M[0][0], model.M[1][0], model.M[2][0]));
        model.Scale(-sec*2);
    }
	//model.SetTranslation(0, 0.001,0);
    //model.Rotate(sec, Vector3(0,sec,0));
    //model.Rotate(sec*10, Vector3(0,0,sec));
    //model.Scale(sec*100);

}


