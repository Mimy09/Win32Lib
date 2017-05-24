#pragma once
#include "tkState.h"

namespace tk {
	class StateManager {
	public:
		StateManager();
		~StateManager();

		void SetState(tk::State* state);
		inline GAME_STATE GetState() { return m_currentState->GetState(); }
		inline void Update() { m_currentState->OnUpdate(); }

	private:
		tk::State* m_currentState;
	};
}