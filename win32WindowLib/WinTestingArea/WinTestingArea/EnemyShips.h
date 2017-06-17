#pragma once
#include "Enemy.h"
namespace game {
	class ShipEasyEnemy : public Enemy {
	public:
		ShipEasyEnemy() {
			m_health = 20;
			m_damage = 25;
			m_speed = 10;
		}
		~ShipEasyEnemy() {}
	};
	class ShipMediumEnemy : public Enemy {
	public:
		ShipMediumEnemy() {
			m_health = 30;
			m_damage = 50;
			m_speed = 10;
		}
		~ShipMediumEnemy() {}
	};
	class ShipHardEnemy : public Enemy {
	public:
		ShipHardEnemy() {
			m_health = 50;
			m_damage = 75;
			m_speed = 15;
		}
		~ShipHardEnemy() {}
	};
}