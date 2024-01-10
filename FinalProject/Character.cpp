#include "Character.h"

Character::Character() {
	Init();
}

void Character::Init() {
	halfCharacterWidth = character_width / 2;
	x = window_width / 2;
	y = ground - halfCharacterWidth;
	speed = character_speed;
	state = CharacterState::IDLE;
}
void Character::Update() {
	state = CharacterState::IDLE;
	if (key_state[ALLEGRO_KEY_A] || key_state[ALLEGRO_KEY_LEFT]) {
		x -= speed;
		x = x >= 0 ? x : 0;
		state = CharacterState::LEFT;
	}
	if (key_state[ALLEGRO_KEY_D] || key_state[ALLEGRO_KEY_RIGHT]) {
		x += speed;
		x = x <= window_width ? x : window_width;
		state = CharacterState::RIGHT;
	}
}

void Character::Draw() {
	al_draw_rectangle(x - halfCharacterWidth, y - halfCharacterWidth, x + halfCharacterWidth, y + halfCharacterWidth, al_map_rgb(255, 255, 255), 5.0);
	switch (state) {
	case CharacterState::LEFT:
		al_draw_filled_rectangle(
			x - halfCharacterWidth + 0.2 * character_width, y - halfCharacterWidth + 0.3 * character_width,
			x - halfCharacterWidth + 0.3 * character_width, y - halfCharacterWidth + 0.4 * character_width,
			al_map_rgb(255, 255, 255));
		break;
	case CharacterState::RIGHT:
		al_draw_filled_rectangle(
			x + halfCharacterWidth - 0.2 * character_width, y - halfCharacterWidth + 0.3 * character_width,
			x + halfCharacterWidth - 0.3 * character_width, y - halfCharacterWidth + 0.4 * character_width,
			al_map_rgb(255, 255, 255));
		break;
	case CharacterState::IDLE:
		al_draw_filled_rectangle(
			x - halfCharacterWidth + 0.25 * character_width, y - halfCharacterWidth + 0.3 * character_width,
			x - halfCharacterWidth + 0.35 * character_width, y - halfCharacterWidth + 0.4 * character_width,
			al_map_rgb(255, 255, 255));
		al_draw_filled_rectangle(
			x + halfCharacterWidth - 0.25 * character_width, y - halfCharacterWidth + 0.3 * character_width,
			x + halfCharacterWidth - 0.35 * character_width, y - halfCharacterWidth + 0.4 * character_width,
			al_map_rgb(255, 255, 255));
		break;
	default:
		break;
	}
}

