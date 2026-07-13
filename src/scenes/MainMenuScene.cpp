#include "MainMenuScene.hpp"
#include "common/Vector2.hpp"
#include "core/CoreApp.hpp"
#include "objects/GameObject.hpp"
#include "render/Framebuffer.hpp"
#include "render/Rectangle.hpp"
#include "input/InputManager.hpp"

namespace scenes {
	struct MainMenuScene::Impl {
		float loadingThreshold = 2.f;
		float currentTime = 0.f;

		std::vector<objects::GameObject> objectsVector;

		void draw() {
			for (const auto& obj : objectsVector) {
				render::Rectangle::draw(obj.pos, obj.size, obj.color);
			}
		}
	};

	MainMenuScene::MainMenuScene() : d(new Impl()) {
		d->objectsVector.reserve(2);

		auto blue_rectangle = objects::GameObject{};
		blue_rectangle.pos = common::Vector2{100, 100};
		blue_rectangle.size = common::Vector2{20, 20};
		blue_rectangle.color = 0xFF0000FF;

		auto red_rectangle = objects::GameObject{};
		red_rectangle.pos = common::Vector2{150, 100};
		red_rectangle.size = common::Vector2{20, 20};
		red_rectangle.color = 0xFFFF0000;

		d->objectsVector.emplace_back(blue_rectangle);
		d->objectsVector.emplace_back(red_rectangle);
	}

	MainMenuScene::~MainMenuScene() {
		delete d;
	}

	void MainMenuScene::update(float dt) {
	//	auto random_uint32 = []() -> uint32_t {
	//		return ((uint32_t)random() << 16) ^ (uint32_t)random();
	//	};
	//	render::Framebuffer::instance()->clear(random_uint32());
		render::Framebuffer::instance()->clear(0xFF000000);
		d->draw();

		static float speed = 2.f;
		auto *red = &d->objectsVector[1];
		red->pos.x += speed;
		if (red->pos.x + red->size.x >= core::CoreApp::instance()->getWidth()) {
			speed = -2.f;
		}
		if (red->pos.x <= 0.f) {
			speed = 2.f;
		}
	}
}
