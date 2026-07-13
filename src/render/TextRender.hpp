#pragma once
#include <string_view>
#include <common/Vector2.hpp>

namespace render {
	class TextRender {
	public:
		static void drawText(std::string_view txt, const common::Vector2& size, uint32_t color);
	};
}