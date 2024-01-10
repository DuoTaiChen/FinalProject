#ifndef MAINSCENE_H_INCLUDE
#define MAINSCENE_H_INCLUDE

#include"Character.h"
#include"Ball.h"
#include"AddingScore.h"
#include"Lightning.h"

class MainScene
{
public:
	MainScene();

	void Update();
	bool IsEnd() { return isEnd; }
	double GetRecord() { return record; }
	~MainScene();
private:
	void game_init();
	void game_destroy();

	bool isEnd;

	Character* character;

	std::unordered_set<Ball*> ball_set;
	int ballGenCounter;
	
	std::unordered_set<Lightning*> lightning_set;
	int lightningGenCounter;

	std::unordered_set<AddingScore*> addScore_set;
	int addingScoreCounter;

	double record;
	int bonus;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER* timer = NULL;

	ALLEGRO_FONT* font;

	ALLEGRO_SAMPLE* backGroundMusic;
	ALLEGRO_SAMPLE_INSTANCE* backGroundMusicInstance;

	ALLEGRO_SAMPLE* bounceSFX;
	ALLEGRO_SAMPLE* lightningSFX;
	ALLEGRO_SAMPLE* scoreSFX;

	ALLEGRO_DISPLAY* display;
};

#endif