#include "Enemy.h"
namespace game {
	Enemy::Enemy() {
		m_entPos = { 100, 100, 50, 50 };
		m_collided = false;
	}

	void Enemy::UpdateEnemy(Player& ply, double deltaTime) {
		if (tk::graphics::Rect::IntersectBox(m_entPos.area().convertRECT(), ply.rect().area().convertRECT())) {
			if (ply.Health() > 0)ply.Health(ply.Health() - (m_damage * (float)deltaTime));
			//if (m_health > 0) m_health -= ply.Damage() * deltaTime;
			m_collided = true;
		} else { m_collided = false; }
	}
}