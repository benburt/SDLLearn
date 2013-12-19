#ifndef _CAPP_H_
    #define _CAPP_H_

#define MAX_FRAMES 60

#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "Ball.h"
 
class CApp {
	enum GAME_STATE
	{
		GAME_STATE_PAUSED,
		GAME_STATE_ACTIVE,
		GAME_STATE_OVER
	};


    private:
        bool    Running;
		SDL_Window* sdlWindow;
		SDL_Renderer* sdlRender;
		//Current displayed image 
		SDL_Surface* gCurrentSurface;
		GAME_STATE gState;
		SDL_Texture* RenderText(std::string message, std::string fontFile, SDL_Color color, int fontSize);
		void DrawScreen(SDL_Renderer* sdlRender);

	
		SDL_Rect midLine; 
    public:
		CApp() {}
 
        int OnExecute();
		int WINDOW_HEIGHT;
		int WINDOW_WIDTH;

		//The surface contained by the window 
		SDL_Surface* gScreenSurface; 
		//The image we will load and show on the screen 
		SDL_Surface* gHelloWorld;
 
    public:
 
        bool Setup();

		SDL_Surface* LoadSurface(std::string path);

        void OnEvent(SDL_Event* Event);
 
        void OnLoop();
 
        void OnRender();
 
        void OnCleanup();
};
 
#endif