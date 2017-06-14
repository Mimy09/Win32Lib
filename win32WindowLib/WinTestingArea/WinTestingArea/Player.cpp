#include "Player.h"

Player::Player() {
	ply_forward = ply_back = ply_left = ply_right = false;
	m_entPos = { 200, 200, 30, 30 };
	SetMovment(30.f, 15.f);
	m_health = 100;
}
Player::Player(float x, float y, float width, float height) {
	ply_forward = ply_back = ply_left = ply_right = false;
	m_entPos = { x, y, width, height };
	SetMovment(30.f, 15.f);
}
Player::~Player() {}

void Player::SetMovment(float acceleration, float maxSpeed) {
	m_acceleration_x = m_acceleration_y = acceleration;
	m_max_speed_x = m_max_speed_y = maxSpeed;
	m_vel_x = m_vel_y = 0;
}

void Player::Reset() {
	ply_forward = ply_back = ply_left = ply_right = false;
	m_entPos = { 200, 200, 30, 30 };
	m_health = 100;
}

void Player::UpdatePlayer(double deltaTime, int screenW, int screenH) {
	/* ---- Sharp control ---- */
	/*if (ply_forward && m_entPos.y > 0) { m_entPos.y -= 500 * deltaTime; }
	else if (m_entPos.y < 0){ m_entPos.y = 0; }

	if (ply_back && m_entPos.y < screenH - m_entPos.height) { m_entPos.y += 500 * deltaTime; }
	else if (m_entPos.y > screenH - m_entPos.height) { m_entPos.y = screenH - m_entPos.height; }

	if (ply_left && m_entPos.x > 0) { m_entPos.x -= 500 * deltaTime; }
	else if (m_entPos.x < 0) { m_entPos.x = 0; }

	if (ply_right && m_entPos.x < screenW - m_entPos.width) { m_entPos.x += 500 * deltaTime; }
	else if (m_entPos.x > screenW - m_entPos.width) { m_entPos.x = screenW - m_entPos.width; } */

	/* ---- Smooth control ---- */
	if (m_entPos.y >= 0 && m_entPos.y <= screenH - m_entPos.height) {
		if (ply_forward) {
			if (m_vel_y < m_max_speed_y) {
				if (m_vel_y < 0)m_vel_y += m_acceleration_y * (float)deltaTime * 4;
				else m_vel_y += m_acceleration_y * (float)deltaTime;
			}
		}
		else if (ply_back) {
			if (m_vel_y > -m_max_speed_y) {
				if (m_vel_y > 0)m_vel_y -= m_acceleration_y * (float)deltaTime * 4;
				else m_vel_y -= m_acceleration_y * (float)deltaTime;
			}
		}
		else {
			if (m_vel_y > 0) {
				m_vel_y -= m_acceleration_y * (float)deltaTime * 4;
				if (m_vel_y < 0) m_vel_y = 0;
			}
			else if (m_vel_y < 0) {
				m_vel_y += m_acceleration_y * (float)deltaTime * 4;
				if (m_vel_y > 0) m_vel_y = 0;
			}
		}
	}
	else {
		/* ---- No screen wrap ---- */
		if (m_entPos.y < 0) { m_entPos.y = 0; m_vel_y = 0; }
		if (m_entPos.y > screenH - m_entPos.height) { m_entPos.y = screenH - m_entPos.height; m_vel_y = 0; }

		/* ---- Screen wrap ---- */
		//if (m_entPos.y < 0) { m_entPos.y = screenH - m_entPos.height; }
		//if (m_entPos.y > screenH - m_entPos.height) { m_entPos.y = 0; }
	} m_entPos.y -= m_vel_y;


	if (m_entPos.x >= 0 && m_entPos.x <= screenW - m_entPos.width) {
		if (ply_left) {
			if (m_vel_x < m_max_speed_x) {
				if (m_vel_x < 0)m_vel_x += m_acceleration_x * (float)deltaTime * 4;
				else m_vel_x += m_acceleration_x * (float)deltaTime;
			}
		}
		else if (ply_right) {
			if (m_vel_x > -m_max_speed_x) {
				if (m_vel_x > 0)m_vel_x -= m_acceleration_x * (float)deltaTime * 4;
				else m_vel_x -= m_acceleration_x * (float)deltaTime;
			}
		}
		else {
			if (m_vel_x > 0) {
				m_vel_x -= m_acceleration_x * (float)deltaTime * 4;
				if (m_vel_x < 0) m_vel_x = 0;
			}
			else if (m_vel_x < 0) {
				m_vel_x += m_acceleration_x * (float)deltaTime * 4;
				if (m_vel_x > 0) m_vel_x = 0;
			}
		}
	}
	else {
		/* ---- No screen wrap ---- */
		if (m_entPos.x < 0) { m_entPos.x = 0; m_vel_x = 0; }
		if (m_entPos.x > screenW - m_entPos.width) { m_entPos.x = screenW - m_entPos.width; m_vel_x = 0; }

		/* ---- Screen wrap ---- */
		//if (m_entPos.x < 0) { m_entPos.x = screenW - m_entPos.width; }
		//if (m_entPos.x > screenW - m_entPos.width) { m_entPos.x = 0; }
	} m_entPos.x -= m_vel_x;


	if (m_health < 0) m_health = 0;
	if (m_health == 0) {
		Reset();
	}
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
