#include "Rectangle.hpp"

#include <algorithm>
#include <cstddef>
#include "render/Framebuffer.hpp"

namespace render {
	void Rectangle::draw(const common::Vector2& pos, const common::Vector2& size, uint32_t color) {
		auto framebuffer = Framebuffer::instance();
		uint32_t* pixels = framebuffer->getPixels();
		int x0 = (int)pos.x;
		int y0 = (int)pos.y;

		int x1 = x0 + (int)size.x;
		int y1 = y0 + (int)size.y;
		int framebufferWidth = framebuffer->width();
		int framebufferHeight = framebuffer->height();

		// clip
		x0 = std::max(x0, 0);
		y0 = std::max(y0, 0);

		x1 = std::min(x1, framebufferWidth);
		y1 = std::min(y1, framebufferHeight);

		for (int y = y0; y < y1; y++) {
			uint32_t* row = pixels + static_cast<ptrdiff_t>(y * framebufferWidth);

			for (int x = x0; x < x1; x++) {
				row[x] = color;
			}
		}
	}
}
