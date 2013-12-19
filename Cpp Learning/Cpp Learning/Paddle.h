#include <SDL.h>

class Paddle
{

public:
	int PADDLE_HEIGHT;
	static const int PADDLE_WIDTH = 15;
	int PADDLE_X;
	int PADDLE_Y;
	int PADDLE_VELOCITY;

	void SetLocation(int x, int y);
	void Draw(SDL_Renderer* render);
	void Update(int x, int y);
	
	void Move(bool up);
};