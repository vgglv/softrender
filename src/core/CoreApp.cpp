#include "CoreApp.hpp"
#include "render/Rectangle.hpp"
#include "state/StateMachine.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

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
	};

	CoreApp* CoreApp::instance() {
		assert(myInstance != nullptr);
		return myInstance;
	}

	CoreApp::CoreApp() : d(new Impl()) {
		d->width = 800;
		d->height = 800;
		d->framebufferVector.reserve(d->width * d->height);
		for (size_t i = 0; i < d->width * d->height; i++) {
			d->framebufferVector.emplace_back(0);
		}
		d->stateMachine = new state::StateMachine();
		assert(myInstance == nullptr);
		myInstance = this;
	}

	CoreApp::~CoreApp() {
		delete d;
	}

	void CoreApp::clear(uint32_t color) {
		std::ranges::fill(d->framebufferVector, color);
	}

	void CoreApp::update(float dt) {
		//printf("dt: %.4f\n", dt);
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
