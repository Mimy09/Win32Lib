#pragma once
#include "tkState.h"

namespace tk {
	namespace states {
		

		class StateManager {
		public:
			StateManager();
			~StateManager();

			void SetState(State* state);
			inline GAME_STATE GetState() { return m_currentState->GetState(); }
			inline void Update() { m_currentState->OnUpdate(); }

		private:
			State* m_currentState;
		};
	}
}