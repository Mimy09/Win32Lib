#include "tkStateManager.h"

namespace tk {
	StateManager::StateManager() {
		m_currentState = nullptr;
	}

	StateManager::~StateManager() {
		if (m_currentState != nullptr) {
			delete m_currentState;
			m_currentState = nullptr;
		}
	}
	void StateManager::SetState(tk::State* state) {
		if (m_currentState) m_currentState->OnExit();
		m_currentState = state;
		if (m_currentState) m_currentState->OnEnter();
	}
}