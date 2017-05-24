#pragma once

/****************************************************************************************************
*****************************************************************************************************/
namespace tk {
	enum class GAME_STATE {
		INIT,
		MENU,
		GAME_RUNNING,
		IDLE,
		CLOSING
	};

	class State {
	public:
		State() {}
		virtual ~State() = 0{}
		virtual void OnEnter() {}
		virtual void OnUpdate() {}
		virtual void OnExit() {}

		virtual GAME_STATE GetState() = 0;

	protected:
		int ID;
	};
}
/****************************************************************************************************
*****************************************************************************************************/


namespace tk {
	
	namespace states {
		/* ---- INIT ---- */
		class InitState : public State {
		public:
			InitState() { }
			~InitState() { }

			virtual GAME_STATE GetState() { return GAME_STATE::INIT; }
		private:

		};

		
		/* ---- MENU ---- */
		class MenuState : public State {
		public:
			MenuState() { }
			~MenuState() {}

			virtual GAME_STATE GetState() { return GAME_STATE::MENU; }
		private:

		};


		/* ---- GAME ---- */
		class GameRunningState : public State {
		public:
			GameRunningState() { }
			~GameRunningState() {}

			virtual GAME_STATE GetState() { return GAME_STATE::GAME_RUNNING; }
		private:

		};


		/* ---- IDLE ---- */
		class IdleState : public State {
		public:
			IdleState() {}
			~IdleState() {}

			virtual GAME_STATE GetState() { return GAME_STATE::IDLE; }
		private:

		};


		/* ---- CLOSING ---- */
		class ClosingState : public State {
		public:
			ClosingState() {}
			~ClosingState() {}

			virtual GAME_STATE GetState() { return GAME_STATE::CLOSING; }
		private:

		};

	}
}