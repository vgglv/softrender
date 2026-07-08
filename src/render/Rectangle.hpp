#pragma once
#include "common/Vector2.hpp"
#include <cstdint>

namespace render {
	class Rectangle {
	public:
		static void draw(const common::Vector2& pos, const common::Vector2& size, uint32_t color);
	};
}
