#include "Ball.h"

Ball::Ball(FromLorR fromLorR) {
	Init(fromLorR);
}

Ball::~Ball() {
	Destroy();
}

void Ball::Init(FromLorR fromLorR) {
	r = rand() % ((ball_size_upper / 20 - ball_size_lower / 20) * 20) + ball_size_lower;
	if (fromLorR == FromLorR::LEFT) {
		x = field_left_bound;
		xSpeed = rand() % (ball_speed_upper - ball_speed_lower + 1) + ball_speed_lower;
	}
	else if (fromLorR == FromLorR::RIGHT) {
		x = field_right_bound;
		xSpeed = -(rand() % (ball_speed_upper - ball_speed_lower + 1) + ball_speed_lower);
	}
	y = rand() % (ball_gen_lower - ball_gen_upper) + ball_gen_upper;
	ySpeed = 0;
	gravity = global_gravity;
	isOutRange = false;
	isOnGround = false;
}

void Ball::Destroy() {
}

void Ball::Update() {
	x += xSpeed;
	y += ySpeed += gravity;
	if (y + r >= ground) {
		y = ground - r;
		ySpeed = -ySpeed;
		isOnGround = true;
	}
	else {
		isOnGround = false;
	}
	if (x < field_left_bound || x > field_right_bound) {
		isOutRange = true;
	}
}

void Ball::Draw() {
	al_draw_circle(x, y, r, al_map_rgb(255, 255, 255), 5.0);
}

bool Ball::IsCollision(int characterX, int characterY) {
	if (untouchalbe_for_ball)return false;
	if ((x - characterX) * (x - characterX) + (y - characterY) * (y - characterY) <
		(r + character_width / 2) * (r + character_width / 2)) {
		return true;
	}
	return false;
}
