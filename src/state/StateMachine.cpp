#include "StateMachine.hpp"
#include "render/Rectangle.hpp"
#include "core/CoreApp.hpp"

namespace state {
	StateMachine::StateMachine() = default;

	StateMachine::~StateMachine() = default;

	void StateMachine::update(float dt) {
		switch (currentState) {
			case GameState::TITLE_SCREEN: {
				//	auto random_uint32 = []() -> uint32_t {
				//		return ((uint32_t)random() << 16) ^ (uint32_t)random();
				//	};
				//	clear(random_uint32());

				float width = (float)core::CoreApp::instance()->getWidth();
				float height = (float)core::CoreApp::instance()->getHeight();
				common::Vector2 size = {100, 100};
				common::Vector2 pos = {.x = (width / 2.f) - (size.x / 2.f), .y = (height / 2.f) - (size.y / 2.f)};
				render::Rectangle::draw(pos, size, 0xFF0000FF);
			} break;
			case GameState::TITLE_SCREEN_WAIT:
				break;
			case GameState::MAIN_MENU_IN:
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
