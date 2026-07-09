#include "MainMenuScene.hpp"
#include "render/Framebuffer.hpp"

namespace scenes {
	struct MainMenuScene::Impl {
		float loadingThreshold = 2.f;
		float currentTime = 0.f;
	};

	MainMenuScene::MainMenuScene() : d(new Impl()) {}

	MainMenuScene::~MainMenuScene() {
		delete d;
	}

	void MainMenuScene::update(float dt) {
		auto random_uint32 = []() -> uint32_t {
			return ((uint32_t)random() << 16) ^ (uint32_t)random();
		};
		render::Framebuffer::instance()->clear(random_uint32());
	}
}
