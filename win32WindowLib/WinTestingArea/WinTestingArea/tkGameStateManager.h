#pragma once
#include "tkGameStates.h"

namespace tk {
	class GameStateManager {
	public:
		GameStateManager(){}
		~GameStateManager(){}

		void EventHandle();
		inline void SetState(State* state) { currentState = state; }

	private:
		State* currentState;
	};
}