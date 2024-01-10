#include "Menu.h"


Menu::Menu() {
	Init();
}

Menu::~Menu() {
	Destroy();
}

void Menu::Init() {
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	al_install_mouse();
	al_install_keyboard();
	al_install_audio();

	al_reserve_samples(20);
	hoverSFX = al_load_sample("hoverSFX.mp3");
	menuMusic = al_load_sample("menu.mp3");
	menuMusicInstance = al_create_sample_instance(menuMusic);

	al_set_sample_instance_playmode(menuMusicInstance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(menuMusicInstance, 1);
	al_attach_sample_instance_to_mixer(menuMusicInstance, al_get_default_mixer());
	al_play_sample_instance(menuMusicInstance);

	display = al_create_display(window_width, window_height);
	timer = al_create_timer(fps);
	event_queue = al_create_event_queue();
	titleFont = al_load_font("Cracker Winter.ttf", 96, 0);
	buttonFont = al_load_font("Cracker Winter.ttf", 48, 0);

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	state = MenuState::MENU;

	titleX = 50;
	titleY = 50;

	buttonWidth = 250;
	buttonHeight = 50;

	startX = buttonWidth / 2;
	startY = window_height / 2.5;

	tutorialX = startX;
	tutorialY = startY + buttonHeight + 20;

	exitX = startX;
	exitY = tutorialY + buttonHeight + 20;

	ballGenCounter = 0;
	lightningGenCounter = 0;

	al_start_timer(timer);
}

void Menu::Destroy() {
	al_destroy_sample_instance(menuMusicInstance);
	al_destroy_sample(menuMusic);
	al_destroy_sample(hoverSFX);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_font(titleFont);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_audio();
}

void Menu::Update() {
	al_wait_for_event(event_queue, &event);
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		state = MenuState::EXIT;
	}

	bool mouseInHover = startIsHover || tutorialIsHover || exitIsHover;
	if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
		mouseX = event.mouse.x;
		mouseY = event.mouse.y;

		startIsHover = IsHover(startX, startY);
		tutorialIsHover = IsHover(tutorialX, tutorialY);
		exitIsHover = IsHover(exitX, exitY);

		if (!mouseInHover && (startIsHover || tutorialIsHover || exitIsHover)) {
			al_play_sample(hoverSFX, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (state != MenuState::TUTORIAL) {
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
				state = MenuState::GAME;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_T) {
				state = MenuState::TUTORIAL;
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				state = MenuState::EXIT;
			}
		}
		else
			state = MenuState::MENU;
	}

	if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (state == MenuState::TUTORIAL) {
			state = MenuState::MENU;
		}
		else {
			if (startIsHover) {
				state = MenuState::GAME;
			}
			if (tutorialIsHover) {
				state = MenuState::TUTORIAL;
			}
			if (exitIsHover) {
				state = MenuState::EXIT;
			}
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

		lightningGenCounter++;
		if (lightningGenCounter == lightning_gen_rate) {
			int lightningNum = rand() % (lightning_gen_upper - lightning_gen_lower + 1) + lightning_gen_lower;
			for (int i = 0; i < lightningNum; i++) {
				lightning_set.insert(new Lightning());
			}
			lightningGenCounter = 0;
		}

		for (auto lightning_it = lightning_set.begin(); lightning_it != lightning_set.end();) {
			(*lightning_it)->Update();
			if ((*lightning_it)->GetState() == LightningState::END) {
				lightning_it = lightning_set.erase(lightning_it);
			}
			else {
				(*lightning_it)->Draw();
				lightning_it++;
			}
		}

		if (state == MenuState::TUTORIAL) {
			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 50, window_height / 2, 0, "Go Left:");
			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 50, window_height / 2 + 50, 0, "A / arrowLeft");
			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 1000, window_height / 2, 0, "Go Right:");
			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 1000, window_height / 2 + 50, 0, "D / arrowRight");
		}
		else if (state == MenuState::MENU) {
			al_draw_text(titleFont, al_map_rgb(255, 255, 255), titleX, titleY, 0, game_name);

			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), startX, startY, 0, "Start (Space)");
			if (startIsHover)
				al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 0, startY, 0, "-----");

			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), tutorialX, tutorialY, 0, "Tutorial (T)");
			if (tutorialIsHover)
				al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 0, tutorialY, 0, "-----");

			al_draw_text(buttonFont, al_map_rgb(255, 255, 255), exitX, exitY, 0, "Exit (ESC)");
			if (exitIsHover)
				al_draw_text(buttonFont, al_map_rgb(255, 255, 255), 0, exitY, 0, "-----");
		}

		al_flip_display();
	}
}

bool Menu::IsHover(int targetX, int targetY) {
	if (abs(targetX + 100 - mouseX) < buttonWidth / 2 && abs(targetY + 20 - mouseY) < buttonHeight / 2) {
		return true;
	}
	return false;
}

