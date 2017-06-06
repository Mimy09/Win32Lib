#include "Player.h"

Player::Player() {
	ply_forward = ply_back = ply_left = ply_right = false;
	ply_rect = { 200, 200, 30, 30 };

	ply_gRect = {
		tk::math::Vec2{ ply_rect.x, ply_rect.y },
		tk::math::Vec2{ ply_rect.x + ply_rect.width, ply_rect.y },
		tk::math::Vec2{ ply_rect.x + ply_rect.width, ply_rect.y + ply_rect.height },
		tk::math::Vec2{ ply_rect.x, ply_rect.y + ply_rect.height }
	};

	SetMovment(30.f, 15.f);
}
Player::Player(float x, float y, float width, float height) {
	ply_forward = ply_back = ply_left = ply_right = false;
	ply_rect = { x, y, width, height };
	SetMovment(30.f, 15.f);
}
Player::~Player() {}

void Player::SetMovment(float acceleration, float maxSpeed) {
	m_acceleration_x = m_acceleration_y = acceleration;
	m_max_speed_x = m_max_speed_y = maxSpeed;
	m_vel_x = m_vel_y = 0;
}

void Player::Draw(HDC hdc) {
	ply_gRect.Draw(hdc);
	//Rectangle(hdc, (int)ply_rect.x, (int)ply_rect.y, (int)ply_rect.area().width, (int)ply_rect.area().height);
}

void Player::Update(double deltaTime, int screenW, int screenH) {
	/* ---- Sharp control ---- */
	/*if (ply_forward && ply_rect.y > 0) { ply_rect.y -= 500 * deltaTime; }
	else if (ply_rect.y < 0){ ply_rect.y = 0; }
		
	if (ply_back && ply_rect.y < screenH - ply_rect.height) { ply_rect.y += 500 * deltaTime; }
	else if (ply_rect.y > screenH - ply_rect.height) { ply_rect.y = screenH - ply_rect.height; }

	if (ply_left && ply_rect.x > 0) { ply_rect.x -= 500 * deltaTime; }
	else if (ply_rect.x < 0) { ply_rect.x = 0; }

	if (ply_right && ply_rect.x < screenW - ply_rect.width) { ply_rect.x += 500 * deltaTime; }
	else if (ply_rect.x > screenW - ply_rect.width) { ply_rect.x = screenW - ply_rect.width; } */

	/* ---- Smooth control ---- */
	if (ply_rect.y >= 0 && ply_rect.y <= screenH - ply_rect.height) {
		if (ply_forward) {
			if (m_vel_y < m_max_speed_y) {
				if (m_vel_y < 0)m_vel_y += m_acceleration_y * (float)deltaTime * 4;
				else m_vel_y += m_acceleration_y * (float)deltaTime;
			}
		} else if (ply_back) {
			if (m_vel_y > -m_max_speed_y) {
				if (m_vel_y > 0)m_vel_y -= m_acceleration_y * (float)deltaTime * 4;
				else m_vel_y -= m_acceleration_y * (float)deltaTime;
			}
		} else{
			if (m_vel_y > 0) {
				m_vel_y -= m_acceleration_y * (float)deltaTime * 4;
				if (m_vel_y < 0) m_vel_y = 0;
			} else if (m_vel_y < 0) {
				m_vel_y += m_acceleration_y * (float)deltaTime * 4;
				if (m_vel_y > 0) m_vel_y = 0;
			}
		}
	} else { 
		/* ---- No screen wrap ---- */
		if (ply_rect.y < 0) { ply_rect.y = 0; m_vel_y = 0; }
		if (ply_rect.y > screenH - ply_rect.height) { ply_rect.y = screenH - ply_rect.height; m_vel_y = 0; }

		/* ---- Screen wrap ---- */
		//if (ply_rect.y < 0) { ply_rect.y = screenH - ply_rect.height; }
		//if (ply_rect.y > screenH - ply_rect.height) { ply_rect.y = 0; }
	} ply_rect.y -= m_vel_y;
	

	if (ply_rect.x >= 0 && ply_rect.x <= screenW - ply_rect.width) {
		if (ply_left) {
			if (m_vel_x < m_max_speed_x) {
				if (m_vel_x < 0)m_vel_x += m_acceleration_x * (float)deltaTime * 4;
				else m_vel_x += m_acceleration_x * (float)deltaTime;
			}
		} else if (ply_right) {
			if (m_vel_x > -m_max_speed_x) {
				if (m_vel_x > 0)m_vel_x -= m_acceleration_x * (float)deltaTime * 4;
				else m_vel_x -= m_acceleration_x * (float)deltaTime;
			}
		} else {
			if (m_vel_x > 0) {
				m_vel_x -= m_acceleration_x * (float)deltaTime * 4;
				if (m_vel_x < 0) m_vel_x = 0;
			} else if (m_vel_x < 0) {
				m_vel_x += m_acceleration_x * (float)deltaTime * 4;
				if (m_vel_x > 0) m_vel_x = 0;
			}
		}
	} else {
		/* ---- No screen wrap ---- */
		if (ply_rect.x < 0) { ply_rect.x = 0; m_vel_x = 0; }
		if (ply_rect.x > screenW - ply_rect.width) { ply_rect.x = screenW - ply_rect.width; m_vel_x = 0; }

		/* ---- Screen wrap ---- */
		//if (ply_rect.x < 0) { ply_rect.x = screenW - ply_rect.width; }
		//if (ply_rect.x > screenW - ply_rect.width) { ply_rect.x = 0; }
	} ply_rect.x -= m_vel_x;

	ply_gRect = {
		tk::math::Vec2{ ply_rect.x, ply_rect.y },
		tk::math::Vec2{ ply_rect.x + ply_rect.width, ply_rect.y },
		tk::math::Vec2{ ply_rect.x + ply_rect.width, ply_rect.y + ply_rect.height },
		tk::math::Vec2{ ply_rect.x, ply_rect.y + ply_rect.height }
	};
}

void Player::OnKeyUp(UINT key) {
	switch (key) {
	case VK_UP:
	case 'W': ply_forward = false; break;
	case VK_DOWN:
	case 'S': ply_back = false; break;
	case VK_LEFT:
	case 'A': ply_left = false; break;
	case VK_RIGHT:
	case 'D': ply_right = false; break;
	default:
		break;
	}
}

void Player::OnKeyDown(UINT key) {
	switch (key) {
	case VK_UP:
	case 'W': ply_forward = true; break;
	case VK_DOWN:
	case 'S': ply_back = true; break;
	case VK_LEFT:
	case 'A': ply_left = true; break;
	case VK_RIGHT:
	case 'D': ply_right = true; break;
	default:
		break;
	}
}
