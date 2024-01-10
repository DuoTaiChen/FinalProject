#ifndef BALL_H_INCLUDE
#define BALL_H_INCLUDE

#include "global.h"

enum class FromLorR
{
	LEFT,
	RIGHT
};

class Ball
{
public:
	Ball(FromLorR fromLorR);
	~Ball();
	void Draw();
	void Update();
	bool IsOutRange() { return isOutRange; }
	bool IsOnGround() { return isOnGround; }
	bool IsCollision(int characterX, int characterY);
private:
	void Init(FromLorR);
	void Destroy();
	float x, y;
	int r;
	float xSpeed, ySpeed;
	float gravity;
	bool isOutRange;
	bool isOnGround;
};
#endif

