#pragma once
#include <Windows.h>
#include <tkWindow.h>
#include "tkGraphics.h"

class Player {
public:
	Player();
	Player(float x, float y, float width, float height);
	~Player();

	void Draw(HDC hdc);
	void Update(double deltaTime, float screenW, float screenH);
	void OnKeyUp(UINT key);
	void OnKeyDown(UINT key);

	void SetMovment(float acceleration, float maxSpeed);

	inline tk::graphics::Rect rect() { return ply_rect; }

	float m_vel_y, m_acceleration_y, m_max_speed_y;
	float m_vel_x, m_acceleration_x, m_max_speed_x;
private:
	tk::graphics::Rect ply_rect;
	bool ply_forward, ply_back, ply_left, ply_right;

};