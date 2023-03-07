#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h"
#include <GLUT/glut.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>


Camera c;
int type_c = -1;
Vector3 lukat_x = Vector3(0, 0, 1);
float near= 0;
float far = 0;
float near_p = 0;
float far_p = 0;

Mesh* quad_mesh = new Mesh();
Shader* shader;




Application::Application(const char* caption, int width, int height)
{
    this->window = createWindow(caption, width, height);

    int w,h;
    SDL_GetWindowSize(window,&w,&h);

    this->mouse_state = 0;
    this->time = 0.f;
    this->window_width = w;
    this->window_height = h;
    this->keystate = SDL_GetKeyboardState(nullptr);

    this->framebuffer.Resize(w, h);
       

}

Application::~Application()
{

}

void Application::Init(void)
{
    std::cout << "Initiating app..." << std::endl;
    c = Camera();
    c.SetPerspective(45, 1, .01, 100);
    c.LookAt(lukat_x, Vector3(near, 0, 0), Vector3::UP);
    c.LookAt(lukat_x, Vector3(near_p, 0, 0), Vector3::UP);
    
    shader = Shader::Get("a.vd","a.fs");

}


void Application::Render(void){
    
    int primitive = 0;
    quad_mesh->Render(primitive);
    
    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f};
    
    glViewport(0, 0, 800, 600);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(program_handler);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,vVertices);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glFinish();

    /*
    //Clear the framebuffer and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Draw scene
    
    //Swap between front and back buffer
    //This method name changes depending on the platform
    //glutSwapBuffers();
    glFinish();
    */
}
// Called after render
void Application::Update(float seconds_elapsed){
    
}

//keyboard press event
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    
    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch(event.keysym.sym) {
        case SDLK_ESCAPE:
            exit(0);
            break; // ESC key, kill the app
            
        case SDLK_c: //To lock camera
            type_c *= -1;
            break;
        
    }
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
    if (event.button == SDL_BUTTON_LEFT) {

    }
}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
    if (event.button == SDL_BUTTON_LEFT) {

    }
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
    if (type_c == 1){
        c.Move(Vector3(-mouse_delta.x*0.01,mouse_delta.y*0.01,0));
    }
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
    
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}

