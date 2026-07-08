#include "CoreApp.hpp"
#include <algorithm>
#include <cassert>
#include "render/Rectangle.hpp"

namespace {
	core::CoreApp* myInstance = nullptr;
}

namespace core {
	CoreApp* CoreApp::instance() {
		assert(myInstance != nullptr);
		return myInstance;
	}

	CoreApp::CoreApp() : _width(800), _height(800), _framebufferVector(_width * _height) {
		assert(myInstance == nullptr);
		myInstance = this;
	}

	CoreApp::~CoreApp() = default;

	void CoreApp::clear(uint32_t color) {
		std::ranges::fill(_framebufferVector, color);
	}

	void CoreApp::render() {
		//	auto random_uint32 = []() -> uint32_t {
		//		return ((uint32_t)random() << 16) ^ (uint32_t)random();
		//	};
		//	clear(random_uint32());
		clear(0xFFFF0000);

		common::Vector2 size = {100, 100};
		common::Vector2 pos = {
			.x = ((float)getWidth() / 2.f) - (size.x / 2.f),
			.y = ((float)getHeight() / 2.f) - (size.y / 2.f)
		};
		render::Rectangle::draw(pos, size, 0xFF0000FF);
	}

	uint32_t* CoreApp::getFramebuffer() {
		return _framebufferVector.data();
	}

	int CoreApp::getWidth() const {
		return _width;
	}

	int CoreApp::getHeight() const {
		return _height;
	}

	void CoreApp::setWidth(int width) {
		_width = width;
	}

	void CoreApp::setHeight(int height) {
		_height = height;
	}
}
