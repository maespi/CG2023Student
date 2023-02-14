#pragma once
#include "mesh.h"
#include "image.h"

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


	//Var to identify renderization form
	eRenderMode rMode;

	//Constructors
	Entity();
	Entity(Mesh*);
	Entity(const char*);

	//Destructor
	~Entity();

	//Getters & Setters
	Matrix44 getMatrix() { return model; }
	Mesh* getmesh() { return mesh; }
	void setMatrix(Matrix44 m) { model = m; }
	void setMesh(Mesh* m) { mesh = m; }
	void setMode(eRenderMode a) { rMode = a; }
	eRenderMode getMode() { return rMode; }

	//Render Function
    void Render(Image* framebuffer, Camera* camera, const Color& c);
    void Update(float sec, int type);
};

