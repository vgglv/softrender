#include "TitleScene.hpp"
#include "core/CoreApp.hpp"
#include "common/Vector2.hpp"
#include "render/Rectangle.hpp"
#include "state/GameState.hpp"
#include "state/StateMachine.hpp"

namespace scenes {
	struct TitleScene::Impl {
		float loadingThreshold = 2.f;
		float currentTime = 0.f;
	};

	TitleScene::TitleScene() : d(new Impl()) {}

	TitleScene::~TitleScene() {
		delete d;
	}

	void TitleScene::update(float dt) {
		float width = (float)core::CoreApp::instance()->getWidth();
		float height = (float)core::CoreApp::instance()->getHeight();
		common::Vector2 size = {100, 100};
		common::Vector2 pos = {.x = (width / 2.f) - (size.x / 2.f), .y = (height / 2.f) - (size.y / 2.f)};
		render::Rectangle::draw(pos, size, 0xFF0000FF);

		d->currentTime += dt;

		if (d->currentTime >= d->loadingThreshold) {
			state::StateMachine::instance()->setState(state::GameState::MAIN_MENU_IN);
		}
	}
}
