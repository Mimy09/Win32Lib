#pragma once
#include "tkGraphics.h"
#include "Entity.h"
#include "Player.h"

namespace game {
	/*******************************************************
	********************************************************/
	// Abstract base class for Enemys
	class Enemy : public Entity {
	public:
		Enemy();
		virtual ~Enemy() = 0 {}

		virtual void Health(float health) { m_health = health; }
		virtual float Health() { return m_health; }
		virtual float Damage() { return m_damage; }
		virtual float Speed() { return m_speed; }

		virtual void UpdateEnemy(Player& ply, double deltaTime);

		virtual inline bool Collided() { return m_collided; }

	protected:
		float m_health;
		float m_damage;
		float m_speed;

		bool m_collided;
	};
	/*******************************************************
	********************************************************/
}