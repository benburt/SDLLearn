#include "Ball.h"
#include <string>

Ball::Ball(int x, int y)
{
	this->x = x;
	this->y = y;
	BALL_SPEED_X = 5;
	BALL_SPEED_Y = 5;
}

void Ball::Draw(SDL_Renderer* render)
{
	SDL_RenderDrawLine(render, x, y + (BALL_HEIGHT/2), x + BALL_WIDTH, y + (BALL_HEIGHT/2));
	SDL_RenderDrawLine(render, x + (BALL_WIDTH/2), y, x + (BALL_WIDTH/2), y + BALL_HEIGHT);
}

void Ball::Update(int& score1, int& score2, int WINDOW_HEIGHT, int WINDOW_WIDTH)
{
	x += BALL_SPEED_X; 
	y += BALL_SPEED_Y;
	
	if(x + BALL_WIDTH >= WINDOW_WIDTH || x <= 0)
	{
		BALL_SPEED_X = -BALL_SPEED_X;
		if(x <= 0)
			score2++;
		else if(x + BALL_WIDTH >= WINDOW_WIDTH)
			score1++;
			}
	if(y + BALL_HEIGHT >= WINDOW_HEIGHT || y <= 0)
	{
		BALL_SPEED_Y = -BALL_SPEED_Y;
	}
}