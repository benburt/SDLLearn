#include "Paddle.h"

void Paddle::SetLocation(int x, int y)
{
	PADDLE_X = x;
	PADDLE_Y = y;
	PADDLE_HEIGHT = 150;
	PADDLE_VELOCITY = 3;
}

void Paddle::Draw(SDL_Renderer* render)
{
	SDL_Rect rec;
	rec.x = PADDLE_X;
	rec.y = PADDLE_Y;
	rec.h = PADDLE_HEIGHT;
	rec.w = PADDLE_WIDTH;

	SDL_RenderDrawRect(render, &rec);
	SDL_RenderFillRect(render, &rec);
}

void Paddle::Move(bool up)
{
	if(up == false)
		PADDLE_Y += PADDLE_VELOCITY;
	else
		PADDLE_Y -= PADDLE_VELOCITY;
}