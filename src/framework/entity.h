#pragma once
#include "mesh.h"
#include "image.h"
#include "material.h"

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
    Material material;
    
	//Var to identify renderization form
	eRenderMode rMode;

	//Constructors
	Entity();
	Entity(Mesh*);
	Entity(const char*);

	Entity(Mesh* m, Texture texture);

	Entity(Mesh* m, Texture texture, eRenderMode mod);

	//Destructor
	~Entity();

	//Getters & Setters
	Matrix44 getMatrix() { return model; }
	Mesh* getmesh() { return mesh; }
	void setMatrix(Matrix44 m) { model = m; }
	void setMesh(Mesh* m) { mesh = m; }
	void setMode(eRenderMode a) { rMode = a; }
	eRenderMode getMode() { return rMode; }
	void setTexture(Texture img) { material.setTexture(img); }
	Texture getTexture() { return material.getTexture(); }
	void setMaterial(Material m) { material = m; }
	Material getMaterial() { return material; }

	//Render Function
    void Render(Image* framebuffer, Camera* camera, const Color& c, FloatImage* zBuffer);
    void Update(float sec, int type);
    void Render();
	void Render(Material::sUniformData uniformData);
};

