#pragma once
#include <Windows.h>
#include <tkWindow.h>
#include <tkLinkedList.h>
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

	virtual void Draw(HDC hdc, HPEN hPen);
	void SetMovment(float acceleration, float maxSpeed);

	inline tk::graphics::Rect& rect() { return m_entPos; }
	inline tk::graphics::gRectange g() { return m_entRect; }

	inline float Health() { return m_health; }
	inline void Health(float health) { m_health = health; }

	inline float Damage() { return m_damage; }
	void Reset();

	float m_vel_y, m_acceleration_y, m_max_speed_y;
	float m_vel_x, m_acceleration_x, m_max_speed_x;

	inline float& Fuel() { return m_fuel; }
private:
	tk::std::LinkedList<tk::math::Vec2> m_lines;

	bool ply_forward, ply_back, ply_left, ply_right;
	float m_damage, m_health, m_fuel;
};