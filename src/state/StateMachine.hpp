#pragma once
#include "GameState.hpp"

namespace state {
	class StateMachine {
	public:
		StateMachine();
		~StateMachine();

		void update(float dt);
		void setState(GameState state);
		static StateMachine* instance();

	private:
		struct Impl;
		Impl* d = nullptr;
	};
}
