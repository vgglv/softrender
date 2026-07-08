#include "CoreApp.hpp"
#include <algorithm>

namespace core {
	CoreApp::CoreApp() : _width(800), _height(800), _framebufferVector(_width * _height) {}

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
	}

	const uint32_t* CoreApp::getFramebuffer() const {
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
