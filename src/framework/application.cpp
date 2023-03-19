#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "Material.hpp"
#include "Light.hpp"



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
    
    //camera inits
    c = Camera();
    c.SetPerspective(45, 1, .01, 100);
    c.LookAt( Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3::UP);
    
    
}


void Application::Render(void){
    
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
            
        case SDLK_u: //unlock/lock the cam
            type_c*=-1;
            break;
            
        case SDLK_c: //toggle the usage of the color texture
            break;
            
        case SDLK_s: //toggle the specular texture
            break;
            
        case SDLK_n://to do the same with the normal texture (only for Phong).
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

