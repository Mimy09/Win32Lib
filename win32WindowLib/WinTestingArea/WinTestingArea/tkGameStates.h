#pragma once
#include "tkState.h"

namespace tk {
	class GameRunningState : public State {
	public:
		GameRunningState(){}
		~GameRunningState(){}
		virtual void EventHandle(){
		
		}
	private:

	};

	class GameMenuState: public State {
	public:
		GameMenuState(){}
		~GameMenuState(){}
		virtual void EventHandle(){
		
		}
	private:

	};
}