#include "AddingScore.h"

AddingScore::AddingScore() {
	Init();
}

AddingScore::~AddingScore() {
	Destroy();
}

void AddingScore::Init() {
	font = al_load_font("Cracker Winter.ttf", 48, 0);
	score = rand() % addingScore_range + 1;
	x = rand() % window_width;
	y = 0;
	ySpeed = 0;
	scoreSize = addingScore_size;
	gravity = global_gravity;
}

void AddingScore::Update() {
	y += ySpeed += gravity;
	if (y + scoreSize >= ground) {
		y = ground - scoreSize;
	}
}

void AddingScore::Draw() {
	al_draw_text(font, al_map_rgb(255, 255, 255), x, y, 0, std::to_string(score).c_str());
}

bool AddingScore::IsCollision(int characterX, int characterY) {
	int centerX = x + scoreSize / 2;
	int centerY = y + scoreSize / 2;
	if ((centerX - characterX) * (centerX - characterX) + (centerY - characterY) * (centerY - characterY) <
		(scoreSize / 2 + character_width / 2) * (scoreSize / 2 + character_width / 2)) {
		return true;
	}
	return false;
}

void AddingScore::Destroy() {
	al_destroy_font(font);
}