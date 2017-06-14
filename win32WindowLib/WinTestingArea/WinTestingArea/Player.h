#pragma once
#include <Windows.h>
#include <tkWindow.h>
#include "tkGraphics.h"
#include "Entity.h"

class Player : public game::Entity {
public:
	Player();
	Player(float x, float y, float width, float height);
	~Player();

	void UpdatePlayer(double deltaTime, int screenW, int screenH);
	void OnKeyUp(UINT key);
	void OnKeyDown(UINT key);

	void SetMovment(float acceleration, float maxSpeed);

	inline tk::graphics::Rect rect() { return m_entPos; }
	inline tk::graphics::gRectange g() { return m_entRect; }

	inline float Health() { return m_health; }
	inline void Health(float health) { m_health = health; }

	void Reset();

	float m_vel_y, m_acceleration_y, m_max_speed_y;
	float m_vel_x, m_acceleration_x, m_max_speed_x;
private:
	bool ply_forward, ply_back, ply_left, ply_right;
	float m_health;
};