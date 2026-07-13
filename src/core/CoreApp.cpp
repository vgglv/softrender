#include "CoreApp.hpp"
#include "render/Framebuffer.hpp"
#include "state/StateMachine.hpp"
#include <cassert>
#include <cstddef>
#include <chrono>

namespace {
	core::CoreApp* myInstance = nullptr;
}

namespace core {
	struct CoreApp::Impl {
		int width;
		int height;

		std::unique_ptr<state::StateMachine> stateMachine;
		std::unique_ptr<render::Framebuffer> framebuffer;
		std::chrono::steady_clock::time_point lastTime;
	};

	CoreApp* CoreApp::instance() {
		assert(myInstance != nullptr);
		return myInstance;
	}

	CoreApp::CoreApp(int width, int height) : d(new Impl()) {
		assert(myInstance == nullptr);
		d->lastTime = std::chrono::steady_clock::now();
		d->width = width;
		d->height = height;
		d->stateMachine = std::make_unique<state::StateMachine>();
		d->framebuffer = std::make_unique<render::Framebuffer>(d->width, d->height);
		myInstance = this;
	}

	CoreApp::~CoreApp() {
		delete d;
	}

	void CoreApp::update() {
		auto now = std::chrono::steady_clock::now();
		float dt = std::chrono::duration<float>(now - d->lastTime).count();
		d->lastTime = now;
		d->stateMachine->update(dt);
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
