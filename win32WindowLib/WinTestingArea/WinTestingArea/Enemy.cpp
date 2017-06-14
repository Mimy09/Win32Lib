#include "Enemy.h"
namespace game {
	Enemy::Enemy() {
		m_entPos = { 50, 50, 50, 50 };
	}

	void Enemy::UpdateEnemy(Player& ply) {
		if (tk::graphics::Rect::IntersectBox(m_entPos.area().convertRECT(), ply.rect().area().convertRECT())) {
			ply.Health(ply.Health() - m_damage);
		}
	}
}