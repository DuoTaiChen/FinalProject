#ifndef ENDSCENE_H_INCLUDE
#define ENDSCENE_H_INCLUDE

#include "Global.h"
#include "Ball.h"

enum class EndState {
	ENDSCENE,
	MENU,
	RESTART,
	EXIT,
};

class EndScene {
public:
	EndScene(double record);
	~EndScene();
	EndState GetState() { return state; }
	void Update();
private:
	void Init(double);
	void Destroy();
	bool IsHover(int targetX, int targetY);
	double socre;

	EndState state;
	ALLEGRO_FONT* scoreFont;
	ALLEGRO_FONT* buttonFont;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER* timer;
	ALLEGRO_DISPLAY* display;

	ALLEGRO_SAMPLE* endMusic;
	ALLEGRO_SAMPLE_INSTANCE* endMusicInstance;

	ALLEGRO_SAMPLE* hoverSFX;

	int scoreX, scoreY;
	int bestX, bestY;
	int restartX, restartY;
	int menuX, menuY;
	int exitX, exitY;
	bool restartIsHover, menuIsHover, exitIsHover;
	int buttonWidth;
	int buttonHeight;
	int mouseX, mouseY;

	std::unordered_set<Ball*> ball_set;
	int ballGenCounter;
};

#endif