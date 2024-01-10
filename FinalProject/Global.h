#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_set>

#define fps 1.0/60

#define character_speed 12
#define character_width 70
#define untouchalbe_for_ball false
#define untouchalbe_for_lightning false

#define window_width 1600
#define window_height 900

#define ground window_height * 2 / 3
#define field_right_bound 1800
#define field_left_bound -200

#define global_gravity 0.5

#define ball_size_lower 60
#define ball_size_upper 120
#define ball_speed_lower 3
#define ball_speed_upper 6
#define ball_gen_rate 55
#define ball_gen_upper -100
#define ball_gen_lower 250 

#define addingScore_gen_rate 600
#define addingScore_size 32
#define addingScore_range 3

#define lightning_preview_thickness 1
#define lightning_trigger_thickness 10
#define lightning_preview_consist_time 180
#define lightning_preview_interval_time 30
#define lightning_trigger_consist_time 30
#define lightning_gen_rate 300
#define lightning_gen_lower 2
#define lightning_gen_upper 4

#define game_name "Attack On Ball&Lightning"

extern bool key_state[ALLEGRO_KEY_MAX];
#endif
