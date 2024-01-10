#ifndef CHARACTER_H_INCLUDE
#define CHARACTER_H_INCLUDE

#include "global.h"

enum class CharacterState {
	LEFT,
	RIGHT,
	IDLE,
};

class Character {
public:
	Character();
	void Update();
	void Draw();
	int GetX() { return x; }
	int GetY() { return y; }
private:
	void Init();
	int x, y;
	int halfCharacterWidth;
	int spritePos;
	int speed;
	CharacterState state;
};


#endif