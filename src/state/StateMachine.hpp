#pragma once
#include "GameState.hpp"

namespace state {
	class StateMachine {
	public:
		StateMachine();
		~StateMachine();

		void update(float dt);

	private:
		GameState currentState = GameState::TITLE_SCREEN;
	};
}
