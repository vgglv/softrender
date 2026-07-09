#include "Framebuffer.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>

namespace {
	render::Framebuffer* myInstance = nullptr;
}

namespace render {
	Framebuffer* Framebuffer::instance() {
		assert(myInstance != nullptr);
		return myInstance;
	}

	Framebuffer::Framebuffer(int width, int height) : _framebufferVector(static_cast<size_t>(width * height)), _width(width), _height(height) {
		assert(myInstance == nullptr);
		myInstance = this;
	}

	void Framebuffer::clear(uint32_t color) {
		std::ranges::fill(_framebufferVector, color);
	}

	uint32_t* Framebuffer::getPixels() {
		return _framebufferVector.data();
	}

	int Framebuffer::width() const {
		return _width;
	}

	int Framebuffer::height() const {
		return _height;
	}
}
