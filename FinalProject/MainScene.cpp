#include "MainScene.h"


MainScene::MainScene() {
	game_init();
}

MainScene::~MainScene() {
	game_destroy();
}

void MainScene::game_init() {
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	al_install_keyboard();
	al_install_audio();

	al_reserve_samples(100);
	bounceSFX = al_load_sample("ball3.mp3");
	lightningSFX = al_load_sample("lightning.mp3");
	scoreSFX = al_load_sample("score.mp3");
	backGroundMusic = al_load_sample("background.mp3");
	backGroundMusicInstance = al_create_sample_instance(backGroundMusic);

	al_set_sample_instance_playmode(backGroundMusicInstance, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(backGroundMusicInstance, 1);
	al_attach_sample_instance_to_mixer(backGroundMusicInstance, al_get_default_mixer());
	al_play_sample_instance(backGroundMusicInstance);

	character = new Character();
	display = al_create_display(window_width, window_height);
	event_queue = al_create_event_queue();
	timer = al_create_timer(fps);
	font = al_load_font("Cracker Winter.ttf", 64, 0);

	srand(time(NULL));
	ballGenCounter = 0;
	addingScoreCounter = 0;
	lightningGenCounter = 0;
	isEnd = false;
	record = 0;
	bonus = 0;

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
}

void MainScene::game_destroy() {
	al_destroy_sample(bounceSFX);
	al_destroy_sample(lightningSFX);
	al_destroy_sample(scoreSFX);
	al_destroy_sample(backGroundMusic);
	al_destroy_sample_instance(backGroundMusicInstance);
	al_destroy_display(display);
	delete(character);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font);
	memset(key_state, false, sizeof(bool) * ALLEGRO_KEY_MAX);
	al_uninstall_keyboard();
	al_uninstall_audio();
}

void MainScene::Update() {
	al_wait_for_event(event_queue, &event);

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		key_state[event.keyboard.keycode] = true;
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) {
		key_state[event.keyboard.keycode] = false;
	}

	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || key_state[ALLEGRO_KEY_ESCAPE]) {
		isEnd = true;
	}

	if (event.type == ALLEGRO_EVENT_TIMER) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_line(0, ground + 5, window_width, ground + 5, al_map_rgb(255, 255, 255), 5);

		record = al_get_timer_count(timer) / 60.0 + bonus;
		al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, std::to_string(record).c_str());

		character->Update();
		character->Draw();

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
			if ((*circle_it)->IsCollision(character->GetX(), character->GetY())) {
				isEnd = true;
			}
			if ((*circle_it)->IsOutRange()) {
				circle_it = ball_set.erase(circle_it);
			}
			else {
				if ((*circle_it)->IsOnGround())al_play_sample(bounceSFX, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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

		if (lightning_set.size() != 0) {
			if ((*lightning_set.begin())->GetShoot()) {
				std::cout << "shoot" << "\n";
				al_play_sample(lightningSFX, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}

		for (auto lightning_it = lightning_set.begin(); lightning_it != lightning_set.end();) {
			(*lightning_it)->Update();

			if ((*lightning_it)->IsCollision(character->GetX())) {
				isEnd = true;
			}
			if ((*lightning_it)->GetState() == LightningState::END) {
				lightning_it = lightning_set.erase(lightning_it);
			}
			else {
				(*lightning_it)->Draw();
				lightning_it++;
			}
		}

		addingScoreCounter++;
		if (addingScoreCounter == addingScore_gen_rate) {
			addScore_set.insert(new AddingScore());
			addingScoreCounter = 0;
		}

		for (auto addingScore_it = addScore_set.begin(); addingScore_it != addScore_set.end();) {
			(*addingScore_it)->Update();
			if ((*addingScore_it)->IsCollision(character->GetX(), character->GetY())) {
				bonus += (*addingScore_it)->GetScore();
				addingScore_it = addScore_set.erase(addingScore_it);
				al_play_sample(scoreSFX, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			else {
				(*addingScore_it)->Draw();
				addingScore_it++;
			}
		}

		al_flip_display();
	}
}


