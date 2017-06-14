#pragma once
#include "EnemyShips.h"
#include <tkexception.h>
namespace game {

	class EnemyFactory {
	public:
		EnemyFactory();
		~EnemyFactory();
		enum ENEMY_TYPE { EASY, MEDIUM, HARD };
		Enemy* CreateEnemy(ENEMY_TYPE EnemyType);
	};
}