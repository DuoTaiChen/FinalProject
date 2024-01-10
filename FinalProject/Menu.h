#ifndef MENU_H_INCLUDE
#define MENU_H_INCLUDE

#include "Global.h"
#include "Ball.h"
#include "Lightning.h"

enum class MenuState
{
	MENU,
	GAME,
	TUTORIAL,
	EXIT,
};

class Menu
{
public:
	Menu();
	~Menu();
	MenuState GetState() { return state; }
	void Update();
private:
	void Init();
	void Destroy();
	bool IsHover(int targetX,int targetY);

	MenuState state;
	ALLEGRO_FONT *titleFont;
	ALLEGRO_FONT *buttonFont;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER *timer;
	ALLEGRO_DISPLAY* display;

	ALLEGRO_SAMPLE* menuMusic;
	ALLEGRO_SAMPLE_INSTANCE* menuMusicInstance;

	ALLEGRO_SAMPLE* hoverSFX;

	int titleX, titleY;
	int startX, startY;
	int tutorialX, tutorialY;
	int exitX, exitY;
	bool startIsHover, tutorialIsHover, exitIsHover;
	int buttonWidth;
	int buttonHeight;
	int mouseX, mouseY;

	std::unordered_set<Ball*> ball_set;
	int ballGenCounter;

	std::unordered_set<Lightning*> lightning_set;
	int lightningGenCounter;
};

#endif