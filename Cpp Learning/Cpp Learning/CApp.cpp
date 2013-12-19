#include "CApp.h"
#include <Windows.h>
#include <direct.h>
#include "Paddle.h"

#define GetCurrentDir _getcwd

char cCurrentPath[FILENAME_MAX];
 
SDL_Texture* texture ;

int playerScore1 = 0;
int playerScore2 = 0;

Ball ball(9, 9);

Paddle playerPaddle;
Paddle aiPaddle;

unsigned int lastTime = 0, currentTime;
int frames = 0;

TTF_Font *font = NULL;

int CApp::OnExecute()
{
	if( Setup() == false)
	{
		printf("SDL Initializing failed: %s", SDL_GetError());
	}
	while(gState == GAME_STATE_ACTIVE || gState == GAME_STATE_PAUSED)
	{
		frames++;
		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000) 
		{
			int currentFPS = frames / (currentTime/1000);
			printf("FPS: %d\n", currentFPS);
			lastTime = currentTime;
		}
		// KEEP CONSISTENT FPS (change so we can still get input)
		if((1000 / MAX_FRAMES) > (SDL_GetTicks() - currentTime) )
				SDL_Delay( (1000/MAX_FRAMES) - (SDL_GetTicks() - currentTime));
		
			SDL_Event event;
			while(SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}
		if(gState == GAME_STATE_ACTIVE)
		{
			OnRender();
			ball.Update(playerScore1,playerScore2, WINDOW_HEIGHT, WINDOW_WIDTH);
			SDL_Event event;
		}
	}
	return 0;
}

bool CApp::Setup()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}
	if((sdlWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, NULL)) == NULL)
	{
		return false;
	}
	if((sdlRender = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL)
	{
		return false;
	}

	if(TTF_Init() < 0)
	{
		return false;
	}

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return false;
	}

	gState = GAME_STATE_ACTIVE;//GAME_STATE_ACTIVE;
	SDL_GetWindowSize(sdlWindow, &WINDOW_WIDTH, &WINDOW_HEIGHT);
	
	aiPaddle.SetLocation(WINDOW_WIDTH - aiPaddle.PADDLE_WIDTH, (WINDOW_HEIGHT/2) - aiPaddle.PADDLE_HEIGHT);
	playerPaddle.SetLocation(0, (WINDOW_HEIGHT/2) - playerPaddle.PADDLE_HEIGHT);

	midLine.h = CApp::WINDOW_HEIGHT;
	midLine.w = 5;
	midLine.x = CApp::WINDOW_WIDTH/2;
	midLine.y = 0;
}

void CApp::OnEvent(SDL_Event* event)
{
	if(event->type == SDL_QUIT)
	{
		SDL_Quit();
		gState = GAME_STATE_OVER;
	}
	else if(event->type == SDL_KEYDOWN)
	{
		switch(event->key.keysym.sym)
		{
		case SDLK_w: playerPaddle.Move(true);break;
		case SDLK_s: playerPaddle.Move(false);break;
		case SDLK_ESCAPE: SDL_Quit();gState = GAME_STATE_OVER; break;
		case SDLK_p: gState = (gState == GAME_STATE_PAUSED) ? GAME_STATE_ACTIVE : GAME_STATE_PAUSED; break;
		}
	}
}
void CApp::OnRender()
{	
	SDL_SetRenderDrawColor(sdlRender, 0, 0, 0, 255);
	SDL_RenderClear(sdlRender);

	SDL_Rect rec;
	rec.x = WINDOW_WIDTH/2 - 72;
	rec.y = 0;
	rec.h = 72;
	rec.w = 150;
	
	SDL_Color color = { 255, 255, 255 };
	char buffer[2];
	itoa(playerScore1, buffer, 10);
	char buf2[2];
	itoa(playerScore2, buf2, 10);

	SDL_RenderCopy(sdlRender, RenderText(std::string(buffer).append(" - ").append(buf2).c_str(), "SourceSansPro-Regular.ttf", color, 64 ), NULL, &rec);
	
	DrawScreen(sdlRender);
	
	ball.Draw(sdlRender);
	playerPaddle.Draw(sdlRender);
	aiPaddle.Draw(sdlRender);

	SDL_RenderPresent(sdlRender);
}

void CApp::DrawScreen(SDL_Renderer* sdlRender)
{
	SDL_SetRenderDrawColor(sdlRender, 255, 255, 255, 255);
	SDL_RenderDrawRect(sdlRender, &midLine);
	SDL_RenderFillRect(sdlRender, &midLine);
}

SDL_Texture* CApp::RenderText(std::string message, std::string fontFile, SDL_Color color, int fontSize)
{
	if(font == NULL)
		font = TTF_OpenFont(std::string(cCurrentPath).append("\\" + fontFile).c_str(), fontSize);
	// ERROR LOADING FONT
	if(font == NULL)
		printf("Error: %s", SDL_GetError());
	
	SDL_Texture* text;
	try {
	SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), color);
	text = SDL_CreateTextureFromSurface(sdlRender, surf);
	}catch(std::exception &ex)
	{
		printf("Error: %s", SDL_GetError());
	}

	return text;
}

int main( int argc, char *argv[] ) 
{
	CApp theApp;

	return theApp.OnExecute();
}