#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"



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

    //Initialization lab vars
    type_c = -1;
    texture = new Texture();
    quad_mesh = new Mesh();
    opt = 1;
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
    
    //Lab4 inits
    texture->Load("images/fruits.png", true);
    //shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");

    quad_mesh->CreateQuad();
    
}


void Application::Render(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    float asp = (float)framebuffer.width / (float)framebuffer.height;
    
    shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
    shader->Enable();
    
    shader->SetFloat("aspect_ratio", asp);
    shader->SetFloat("center_y", ((float)framebuffer.height/2));
    shader->SetFloat("center_x", ((float)framebuffer.width/2));
    shader->SetFloat("width", ((float)framebuffer.width));
    shader->SetFloat("height", ((float)framebuffer.height));    
    shader->SetFloat("time", time);
    shader->SetUniform1("opt", opt);

    quad_mesh->Render();

    shader->Disable();
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
            
        case SDLK_1:
            opt = 1;
            break;
        case SDLK_2:
            opt = 2;
            break;
        case SDLK_3:
            opt = 3;
            break;
        case SDLK_4:
            opt = 4;
            break;
        case SDLK_5:
            opt = 5;
            break;
        case SDLK_6:
            opt = 6;
            break;
        case SDLK_7:
            opt = 7;
            break;
        case SDLK_8:
            opt = 8;
            break;
        case SDLK_9:
            opt = 9;
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

