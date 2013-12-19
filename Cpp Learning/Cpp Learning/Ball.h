#include <SDL.h>

class Ball
{
static const int BALL_HEIGHT = 18;
static const int BALL_WIDTH = 18;
int BALL_SPEED_X;
int BALL_SPEED_Y;
	
	int x;
	int y;

public:
	Ball(int x, int y);
	Ball() {BALL_SPEED_X = 5; BALL_SPEED_Y = 5;}
	void Draw(SDL_Renderer* render);
	void Update(int& score1, int& score2, int WINDOW_HEIGHT, int WINDOW_WIDTH);
};