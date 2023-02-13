/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"
#define NUMPART 100

class Application{
public:

	// Window

	SDL_Window* window;
	int window_width;
	int window_height;

	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
};
    
class Animation{ //type of class Animation
public:
    Image img;
    particle particles[NUMPART];
    
    Animation(){
        img.Resize(0, 0);
        for (int i= 0;i<NUMPART;i++){
            particles[i] = particle();
        }
    }
    void SetAnimation(int v, int w, int h){
        img.Resize(w, h);
        img.Fill(Color (0,0,0));
        for (int i= 0;i<NUMPART;i++){
            int x = rand()%w;
            int y = rand()%h;
            int r = rand()%256;
            int g = rand()%256;
            int b = rand()%256;
            particles[i].set(x, y, v,r,g,b);
        }

    }
    void UpdateAnimation(float time){ //update animation
        for (int i = 0; i<NUMPART; i++){
            img.SetPixel(particles[i].posx, particles[i].posy, particles[i].col);
            particles[i].update(time,img.width, img.height);

        }

    }
};
    






