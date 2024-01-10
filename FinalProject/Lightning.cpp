#include "Lightning.h"

Lightning::Lightning() {
	Init();
}

Lightning::~Lightning() {
	Destroy();
}

void Lightning::Init() {
	x = rand() % window_width;
	state = LightningState::PREVIEW;
	previewCounter = 0;
	triggerCounter = 0;
	shoot = false;
}

void Lightning::Destroy() {

}

void Lightning::Update() {
	switch (state)
	{
	case LightningState::PREVIEW:
		previewCounter++;
		if (previewCounter == lightning_preview_consist_time) {
			state = LightningState::TRIGGER;
			shoot = true;
		}
		break;
	case LightningState::TRIGGER:
		shoot = false;
		triggerCounter++;
		if (triggerCounter == lightning_trigger_consist_time) {
			state = LightningState::END;
		}
		break;
	default:
		break;
	}
}

void Lightning::Draw() {
	switch (state)
	{
	case LightningState::PREVIEW:
		if (previewCounter % (lightning_preview_interval_time * 2) - lightning_preview_interval_time < 0) {
			al_draw_line(x, 0, x, ground, al_map_rgb(255, 255, 255), lightning_preview_thickness);
		}
		break;
	case LightningState::TRIGGER:
		al_draw_line(x, 0, x, ground, al_map_rgb(255, 255, 255), lightning_trigger_thickness);
		break;
	case LightningState::END:
		break;
	default:
		break;
	}
}

bool Lightning::IsCollision(int characterX) {
	if (abs(characterX - x) < character_width / 2 + lightning_trigger_thickness / 2 &&
		state == LightningState::TRIGGER &&
		!untouchalbe_for_lightning)
		return true;
	return false;
}