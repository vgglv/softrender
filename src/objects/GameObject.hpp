#pragma once
#include <cstdint>
#include <common/Vector2.hpp>

namespace objects {
	struct GameObject {
		GameObject();
		uint64_t idx = 0;
		common::Vector2 pos;
		common::Vector2 size;
		uint32_t color = 0xFF000000;

		bool valid() const {
			return idx != 0;
		}
	};
}