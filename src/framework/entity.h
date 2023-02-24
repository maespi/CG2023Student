#pragma once
#include "mesh.h"
#include "image.h"

#define NORMAL_REND_TYPE 06440
#define ZBUFFER_REND_TYPE 06450


//Enumeration Draw Tipe
enum class eRenderMode {
    
	POINTCLOUD,
	WIREFRAME,
	TRIANGLES,
	TRIANGLES_INTERPOLATED

};

class Entity
{
public:
	Mesh* mesh;
	Matrix44 model;
    Image* texture;
	bool occlusion;

	//Var to identify renderization form
	eRenderMode rMode;

	//Constructors
	Entity();
	Entity(Mesh*);
	Entity(const char*);

	Entity(Mesh* m, Image* texture);

	Entity(Mesh* m, Image* texture, eRenderMode mod);

	//Destructor
	~Entity();

	//Getters & Setters
	Matrix44 getMatrix() { return model; }
	Mesh* getmesh() { return mesh; }
	void setMatrix(Matrix44 m) { model = m; }
	void setMesh(Mesh* m) { mesh = m; }
	void setMode(eRenderMode a) { rMode = a; }
	eRenderMode getMode() { return rMode; }
	void setTexture(Image* img) { texture = img; }
	Image* getTexture() { return texture; }

	//Render Function
    void Render(Image* framebuffer, Camera* camera, const Color& c, FloatImage* zBuffer);
    void Update(float sec, int type);
};

