#include "EnemyFactory.h"
namespace game {
	EnemyFactory::EnemyFactory() {

	}

	EnemyFactory::~EnemyFactory() {

	}

	Enemy* EnemyFactory::CreateEnemy(ENEMY_TYPE EnemyType) {
		switch (EnemyType) {
		case ENEMY_TYPE::EASY: return new ShipEasyEnemy();
		case ENEMY_TYPE::MEDIUM: return new ShipMediumEnemy();
		case ENEMY_TYPE::HARD: return new ShipHardEnemy();
		default: TK_EXCEPTION("Enemy Factory Error");
		}
	}
}