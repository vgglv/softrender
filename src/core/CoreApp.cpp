#include "CoreApp.hpp"
#include "state/StateMachine.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>
#include <chrono>

namespace {
	core::CoreApp* myInstance = nullptr;
}

namespace core {
	struct CoreApp::Impl {
		int width;
		int height;

		//AARRGGBB
		std::vector<uint32_t> framebufferVector;
		state::StateMachine* stateMachine = nullptr;
		std::chrono::steady_clock::time_point lastTime;
	};

	CoreApp* CoreApp::instance() {
		assert(myInstance != nullptr);
		return myInstance;
	}

	CoreApp::CoreApp() : d(new Impl()) {
		assert(myInstance == nullptr);
		d->lastTime = std::chrono::steady_clock::now();
		d->width = 800;
		d->height = 800;
		d->framebufferVector.reserve(d->width * d->height);
		for (size_t i = 0; i < d->width * d->height; i++) {
			d->framebufferVector.emplace_back(0);
		}
		d->stateMachine = new state::StateMachine();
		myInstance = this;
	}

	CoreApp::~CoreApp() {
		delete d;
	}

	void CoreApp::clear(uint32_t color) {
		std::ranges::fill(d->framebufferVector, color);
	}

	void CoreApp::update() {

		auto now = std::chrono::steady_clock::now();
		float dt = std::chrono::duration<float>(now - d->lastTime).count();
		d->lastTime = now;
		//printf("dt: %.4f\n", dt);

	//	auto random_uint32 = []() -> uint32_t {
	//		return ((uint32_t)random() << 16) ^ (uint32_t)random();
	//	};
	//	clear(random_uint32());

		clear(0xFFFF0000);
		d->stateMachine->update(dt);
	}

	uint32_t* CoreApp::getFramebuffer() {
		return d->framebufferVector.data();
	}

	int CoreApp::getWidth() const {
		return d->width;
	}

	int CoreApp::getHeight() const {
		return d->height;
	}

	void CoreApp::setWidth(int width) {
		d->width = width;
	}

	void CoreApp::setHeight(int height) {
		d->height = height;
	}
}
