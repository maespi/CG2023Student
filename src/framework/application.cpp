#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "entity.h"

std::vector<Entity*> entities;
std::vector<Color> entities_color;
std::vector<Image*> entities_text;
Camera c;
int type_c = -1;
Vector3 lukat_x = Vector3(0.5, 0.25, 1);    //Camera position centered on images
float near_p = 0;
float far_p = 0;


//if you de-comment the lines: 32,38,45 you'll se the animation.
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
    this->zbuffer.Resize(w, h);
}

Application::~Application()
{
    SDL_DestroyWindow(window);
}

void Application::Init(void)
{
    std::cout << "Initiating app..." << std::endl;

    
    
    Mesh* mesh1 = new Mesh();
    mesh1->LoadOBJ("../res/meshes/lee.obj");
    Mesh* mesh2 = new Mesh();
    mesh2->LoadOBJ("../res/meshes/cleo.obj");
     
     

    Mesh* mesh3 = new Mesh();
    mesh3->LoadOBJ("../res/meshes/lee.obj");
    Image* texture3 = new Image(this->window_width, this->window_height);
    texture3->LoadTGA("../res/textures/anna_color_specular.tga");
    
    Image* texture2 = new Image(this->window_width, this->window_height);
    texture2->LoadTGA("../res/textures/cleo_color_specular.tga");
    
    Image* texture1 = new Image(this->window_width, this->window_height);
    texture1->LoadTGA("../res/textures/lee_color_specular.tga");

    Entity* e1 = new Entity(mesh1);
    e1->model.TranslateLocal(1.2, .35, -1.5);
    e1->setMode(eRenderMode::TRIANGLES);
    entities.push_back(e1);
    entities_color.push_back(Color::RED);

    Entity* e2 = new Entity(mesh2);
    e2->setMode(eRenderMode::TRIANGLES);
    e2->model.TranslateLocal(.2, .25, -1);
    entities.push_back(e2);
    entities_color.push_back(Color::BLUE);
     
     

    Entity* e3 = new Entity(mesh3);
    e3->model.TranslateLocal(.6, .5, -1);
    e3->texture = texture3;
    e1->texture = texture1;
    e2->texture = texture2;
    e1->setMode(eRenderMode::TRIANGLES_INTERPOLATED);
    e2->setMode(eRenderMode::TRIANGLES_INTERPOLATED);
    e3->setMode(eRenderMode::TRIANGLES_INTERPOLATED);

    entities.push_back(e3);
    entities_color.push_back(Color::WHITE);
    entities_text.push_back(texture3);
    

    c = Camera();
    c.SetPerspective(45, 1, .01, 100);
    c.LookAt(lukat_x, Vector3(near_p+0.5, .25, 0), Vector3::UP);    //Camera centered on images
}

// Render one frame
void Application::Render(void)
{

    for (int i = 0; i < entities.size(); i++) {
        entities[i]->Render(&framebuffer, &c, entities_color[i], &zbuffer);
    }
    framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed){
    
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->Update(seconds_elapsed,0);//i+1 to update animations
    }

    framebuffer.Fill(Color::BLACK);
}

//keyboard press event
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
    unsigned char r = rand() % 256;
    unsigned char g = rand() % 256;
    unsigned char b = rand() % 256;
    
    // KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch(event.keysym.sym) {
        case SDLK_RIGHT://look right
            c.center.x += 0.05;
            c.UpdateViewMatrix();
            break;
            
        case SDLK_LEFT://look left
            c.center.x -= 0.05;
            c.UpdateViewMatrix();
            break;
            
        case SDLK_UP://zoom in
            c.fov-=0.1;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_DOWN://zoom out
            c.fov+=0.1;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_u: //To lock camera
            type_c *= -1;
            break;
            
        case SDLK_d://++ near plane
            c.near_plane+=0.9;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_a://-- near plane
            c.near_plane-=0.9;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_q://++ far plane
            c.far_plane+=0.9;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_e://-- far plane
            c.far_plane-=0.9;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_w://++ axis y camera
            c.center.y += 0.05;
            c.UpdateViewMatrix();
            break;
            
        case SDLK_s://-- axis y camera
            c.center.y -= 0.05;
            c.UpdateViewMatrix();
            break;
            
        case SDLK_o://set orthographic view
            c.type = c.ORTHOGRAPHIC;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_p://set perspective view
            c.type = c.PERSPECTIVE;
            c.UpdateProjectionMatrix();
            break;
            
        case SDLK_c://Toggle (activate/deactivate) between plain color/interpolated vertex colors
            for (int i = 0; i < entities.size(); i++) {
                if(entities[i]->getMode() == eRenderMode::TRIANGLES)
                    entities[i]->setMode(eRenderMode::TRIANGLES_INTERPOLATED);
                else
                {
                    entities[i]->setMode(eRenderMode::TRIANGLES);
                }
            }
            break;
            
        case SDLK_z://Toggle occlusions
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->occlusion = !entities[i]->occlusion;
            }
            break;
            
        case SDLK_t://Toggle draw mesh with textures
            for (int i = 0; i < entities.size(); i++) {
                if (entities[i]->texture != nullptr) {
                    entities[i]->setTexture(nullptr);
                }
                else
                {
                    entities[i]->setTexture(entities_text[i]);
                }
            }
            break;
            
        case SDLK_ESCAPE:
            exit(0);
            break; // ESC key, kill the app
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

	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}

