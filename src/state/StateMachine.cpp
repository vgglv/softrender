#include "StateMachine.hpp"
#include "render/Rectangle.hpp"
#include "core/CoreApp.hpp"
#include "GameState.hpp"
#include "scenes/TitleScene.hpp"
#include <memory>
#include <cassert>

namespace {
	state::StateMachine* myInstance = nullptr;
}

namespace state {
	struct StateMachine::Impl {
		GameState currentState = GameState::TITLE_SCREEN;

		std::unique_ptr<scenes::TitleScene> titleScene = nullptr;
	};

	StateMachine* StateMachine::instance() {
		assert(myInstance != nullptr);
		return myInstance;
	}

	StateMachine::StateMachine() : d(new Impl()) {
		assert(myInstance == nullptr);
		myInstance = this;
	}

	StateMachine::~StateMachine() {
		delete d;
	}

	void StateMachine::setState(GameState state) {
		d->currentState = state;
	}

	void StateMachine::update(float dt) {
		switch (d->currentState) {
			case GameState::TITLE_SCREEN: {
				d->titleScene = std::make_unique<scenes::TitleScene>();
				d->currentState = GameState::TITLE_SCREEN_WAIT;
			} break;
			case GameState::TITLE_SCREEN_WAIT:
				d->titleScene->update(dt);
				break;
			case GameState::MAIN_MENU_IN:
				d->titleScene.reset();
				break;
			case GameState::MAIN_MENU:
				break;
			case GameState::MAIN_MENU_OUT:
				break;
			case GameState::GAME_SCENE:
				break;
		}
	}
}
