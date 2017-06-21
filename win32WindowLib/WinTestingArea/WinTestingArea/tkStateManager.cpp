#include "tkStateManager.h"

namespace tk {
	namespace states {
		StateManager::StateManager() {
			m_currentState = nullptr;
		}

		StateManager::~StateManager() {
			if (m_currentState != nullptr) {
				delete m_currentState;
				m_currentState = nullptr;
			}
		}
		void StateManager::SetState(State* state) {
			if (m_currentState) m_currentState->OnExit();
			if (m_currentState) {
				delete m_currentState;
				m_currentState = nullptr;
			}
			m_currentState = state;
			if (m_currentState) m_currentState->OnEnter();
		}
	}
}