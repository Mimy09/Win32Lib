#include "Player.h"

Player::Player() {
	ply_rect = { 200, 200, 30, 30 };
	ply_forward = ply_back = ply_left = ply_right = false;
}
Player::Player(float x, float y, float width, float height) {
	ply_rect = { x, y, width, height };
}
Player::~Player() {}

void Player::Draw(HDC hdc) {
	Rectangle(hdc, ply_rect.x, ply_rect.y, ply_rect.area().width, ply_rect.area().height);
}

void Player::Update(double deltaTime, float screenW, float screenH) {
	if (ply_forward && ply_rect.y > 0) { ply_rect.y -= 500 * deltaTime; }
	else if (ply_rect.y < 0){ ply_rect.y = 0; }
		
	if (ply_back && ply_rect.y < screenH - ply_rect.height) { ply_rect.y += 500 * deltaTime; }
	else if (ply_rect.y > screenH - ply_rect.height) { ply_rect.y = screenH - ply_rect.height; }

	if (ply_left && ply_rect.x > 0) { ply_rect.x -= 500 * deltaTime; }
	else if (ply_rect.x < 0) { ply_rect.x = 0; }

	if (ply_right && ply_rect.x < screenW - ply_rect.width) { ply_rect.x += 500 * deltaTime; }
	else if (ply_rect.x > screenW - ply_rect.width) { ply_rect.x = screenW - ply_rect.width; }

}

void Player::OnKeyUp(UINT key) {
	switch (key) {
	case 'W': ply_forward = false; break;
	case 'S': ply_back = false; break;
	case 'A': ply_left = false; break;
	case 'D': ply_right = false; break;
	default:
		break;
	}
}

void Player::OnKeyDown(UINT key) {
	switch (key) {
	case 'W': ply_forward = true; break;
	case 'S': ply_back = true; break;
	case 'A': ply_left = true; break;
	case 'D': ply_right = true; break;
	default:
		break;
	}
}
