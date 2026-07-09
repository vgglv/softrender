#pragma once
#include <cstdint>
#include <vector>

namespace render {
	class Framebuffer {
	public:
		Framebuffer(int width, int height);
		void clear(uint32_t color);
		uint32_t* getPixels();
		int width() const;
		int height() const;

		static Framebuffer* instance();

	private:
		//AARRGGBB
		std::vector<uint32_t> _framebufferVector;
		int _width;
		int _height;
	};
}
