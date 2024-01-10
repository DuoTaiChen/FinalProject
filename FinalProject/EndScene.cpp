#include "EndScene.h"

EndScene::EndScene(double record) {
	Init(record);
}

EndScene::~EndScene() {
	Destroy();
}

void EndScene::Init(double record) {
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	al_install_audio();
	al_install_mouse();
	al_install_keyboard();

	al_reserve_samples(20);
	hoverSFX = al_load_sample("hoverSFX.mp3");
	endMusic = al_load_sample("end.mp3");
	endMusicInstance = al_create_sample_instance(endMusic);

	al_set_sample_instance_playmode(endMusicInstance, ALLEGRO_PLAYMODE_ONCE);
	al_set_sample_instance_gain(endMusicInstance, 1);
	al_attach_sample_instance_to_mixer(endMusicInstance, al_get_default_mixer());
	al_play_sample_instance(endMusicInstance);

	display = al_create_display(window_width, window_height);
	timer = al_create_timer(fps);
	event_queue = al_create_event_queue();
	scoreFont = al_load_font("Cracker Winter.ttf", 96, 0);
	buttonFont = al_load_font("Cracker Winter.ttf", 48, 0);

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	state = EndState::ENDSCENE;

	socre = record;

	scoreX = 50;
	scoreY = 50;

	buttonWidth = 250;
	buttonHeight = 50;

	restartX = buttonWidth / 2;
	restartY = window_height / 2.5;

	menuX = restartX;
	menuY = restartY + buttonHeight + 20;

	exitX = restartX;
	exitY = menuY + buttonHeight + 20;

	ballGenCounter = 0;

	al_start_timer(timer);
}

void EndScene::Destroy() {
	al_destroy_sample(endMusic);
	al_destroy_sample(hoverSFX);
	al_destroy_sample_instance(endMusicInstance);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(scoreFont);
	al_destroy_font(buttonFont);
	al_uninstall_audio();
	al_uninstall_mouse();
	al_uninstall_keyboard();
}

void EndScene::Update() {
	al_wait_for_event(event_queue, &event);
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		state = EndState::EXIT;
	}

	bool mouseInHover = restartIsHover || menuIsHover || exitIsHover;
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
		mouseX = event.mouse.x;
		mouseY = event.mouse.y;

		restartIsHover = IsHover(restartX, restartY);
		menuIsHover = IsHover(menuX, menuY);
		exitIsHover = IsHover(exitX, exitY);

		if (!mouseInHover && (restartIsHover || menuIsHover || exitIsHover)) {
			al_play_sample(hoverSFX, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (restartIsHover) {
			state = EndState::RESTART;
		}
		if (menuIsHover) {
			state = EndState::MENU;
		}
		if (exitIsHover) {
			state = EndState::EXIT;
		}
	}

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (event.keyboard.keycode == ALLEGRO_KEY_R) {
			state = EndState::RESTART;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_M) {
			state = EndState::MENU;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			state = EndState::EXIT;
		}
	}

	if (event.type == ALLEGRO_EVENT_TIMER) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_line(0, ground + 5, window_width, ground + 5, al_map_rgb(255, 255, 255), 5);

		ballGenCounter++;
		if (ballGenCounter == ball_gen_rate) {
			ball_set.insert(new Ball(FromLorR::LEFT));
		}
		else if (ballGenCounter == ball_gen_rate * 2) {
			ball_set.insert(new Ball(FromLorR::RIGHT));
			ballGenCounter = 0;
		}
		for (auto circle_it = ball_set.begin(); circle_it != ball_set.end();) {
			(*circle_it)->Update();
			if ((*circle_it)->IsOutRange()) {
				circle_it = ball_set.erase(circle_it);
			}
			else {
				(*circle_it)->Draw();
				circle_it++;
			}
		}

		if (state == EndState::ENDSCENE) {
			al_draw_text(scoreFont, al_map_rgb(255, 255, 255), scoreX, scoreY, 0, ("Score:" + std::to_string(socre)).c_str());

			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), restartX, restartY, 0, "Restart (R)");
			if (restartIsHover)
				al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 0, restartY, 0, "-----");

			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), menuX, menuY, 0, "Menu (M)");
			if (menuIsHover)
				al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 0, menuY, 0, "-----");

			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), exitX, exitY, 0, "Exit (ESC)");
			if (exitIsHover)
				al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 0, exitY, 0, "-----");
		}

		al_flip_display();
	}
}

bool EndScene::IsHover(int targetX, int targetY) {
	if (abs(targetX + 100 - mouseX) < buttonWidth / 2 && abs(targetY + 20 - mouseY) < buttonHeight / 2) {
		return true;
	}
	return false;
}

