#include "Player.h"

Player::Player() {
	SetMovment(10.f, 500.f);
	Reset();
	m_lines.push_back(tk::math::Vec2{ 400, 300 });
}
Player::Player(float x, float y, float width, float height) {
	ply_forward = ply_back = ply_left = ply_right = false;
	m_entPos = { x, y, width, height };
	SetMovment(30.f, 15.f);
}
Player::~Player() {}

void Player::Draw(HDC hdc, HPEN hPen) {
	Entity::Draw(hdc, hPen);

	//MoveToEx(hdc, (int)m_lines.Find(0).x + 15, (int)m_lines.Find(0).y + 15, NULL);
	//LineTo(hdc, m_entPos.x + 15, m_entPos.y + 15);
}

void Player::SetMovment(float acceleration, float maxSpeed) {
	m_acceleration_x = m_acceleration_y = acceleration;
	m_max_speed_x = m_max_speed_y = maxSpeed;
	m_vel_x = m_vel_y = 0;
}

void Player::Reset() {
	ply_forward = ply_back = ply_left = ply_right = false;
	m_entPos = { 200, 200, 10, 10 };
	m_health = 100;
	m_fuel = 50;
	m_vel_x = m_vel_y = 0;
}

void Player::UpdatePlayer(double deltaTime, int screenW, int screenH) {
	//m_health -= deltaTime * 2;
	if (m_fuel < 0) m_fuel = 0;
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
	if (m_entPos.y >= 0 && m_entPos.y <= screenH - m_entPos.height && m_fuel > 0) {
		if (ply_forward) {
			m_fuel -= (float)deltaTime * 2;
			if (m_vel_y < m_max_speed_y) {
				if (m_vel_y < 0)m_vel_y += m_acceleration_y * (float)deltaTime;
				else m_vel_y += m_acceleration_y * (float)deltaTime;
			}
		}
		else if (ply_back) {
			m_fuel -= (float)deltaTime * 2;
			if (m_vel_y > -m_max_speed_y) {
				if (m_vel_y > 0)m_vel_y -= m_acceleration_y * (float)deltaTime;
				else m_vel_y -= m_acceleration_y * (float)deltaTime;
			}
		}
		else {
			//if (m_vel_y > 0) {
			//	m_vel_y -= m_acceleration_y * (float)deltaTime;
			//	if (m_vel_y < 0) m_vel_y = 0;
			//}
			//else if (m_vel_y < 0) {
			//	m_vel_y += m_acceleration_y * (float)deltaTime;
			//	if (m_vel_y > 0) m_vel_y = 0;
			//}
		}
	}
	else {
		/* ---- No screen wrap ---- */
		//if (m_entPos.y < 0) { m_entPos.y = 0; m_vel_y = 0; }
		//if (m_entPos.y > screenH - m_entPos.height) { m_entPos.y = screenH - m_entPos.height; m_vel_y = 0; }

		/* ---- Screen wrap ---- */
		if (m_entPos.y < 0) { m_entPos.y = screenH - m_entPos.height; }
		if (m_entPos.y > screenH - m_entPos.height) { m_entPos.y = 0; }
	} m_entPos.y -= m_vel_y * (float)deltaTime;


	if (m_entPos.x >= 0 && m_entPos.x <= screenW - m_entPos.width && m_fuel > 0) {
		if (ply_left) {
			m_fuel -= (float)deltaTime * 2;
			if (m_vel_x < m_max_speed_x) {
				if (m_vel_x < 0)m_vel_x += m_acceleration_x * (float)deltaTime;
				else m_vel_x += m_acceleration_x * (float)deltaTime;
			}
		}
		else if (ply_right) {
			m_fuel -= (float)deltaTime * 2;
			if (m_vel_x > -m_max_speed_x) {
				if (m_vel_x > 0)m_vel_x -= m_acceleration_x * (float)deltaTime;
				else m_vel_x -= m_acceleration_x * (float)deltaTime;
			}
		}
		else {
			//if (m_vel_x > 0) {
			//	m_vel_x -= m_acceleration_x * (float)deltaTime;
			//	if (m_vel_x < 0) m_vel_x = 0;
			//}
			//else if (m_vel_x < 0) {
			//	m_vel_x += m_acceleration_x * (float)deltaTime;
			//	if (m_vel_x > 0) m_vel_x = 0;
			//}
		}
	}
	else {
		/* ---- No screen wrap ---- */
		//if (m_entPos.x < 0) { m_entPos.x = 0; m_vel_x = 0; }
		//if (m_entPos.x > screenW - m_entPos.width) { m_entPos.x = screenW - m_entPos.width; m_vel_x = 0; }

		/* ---- Screen wrap ---- */
		if (m_entPos.x < 0) { m_entPos.x = screenW - m_entPos.width; }
		if (m_entPos.x > screenW - m_entPos.width) { m_entPos.x = 0; }
	} m_entPos.x -= m_vel_x * (float)deltaTime;
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
