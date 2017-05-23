#pragma once
namespace tk {
	class State {
	public:
		State() {}
		virtual ~State() = 0 {}

		virtual void EventHandle() = 0{}

		virtual void OnEnter(){}
		virtual void OnExit(){}
	};
}