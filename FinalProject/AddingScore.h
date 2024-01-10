#ifndef ADDINGSCORE_H_INCLUDE
#define ADDINGSCORE_H_INCLUDE

#include "global.h"

class AddingScore {
public:
	AddingScore();
	~AddingScore();
	int GetScore() { return score; }
	void Draw();
	void Update();
	bool IsCollision(int characterX, int characterY);
private:
	void Init();
	void Destroy();
	int score;
	int x, y;
	int scoreSize;
	float ySpeed;
	float gravity;

	ALLEGRO_FONT* font;
};

#endif