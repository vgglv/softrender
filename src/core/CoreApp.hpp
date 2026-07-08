#pragma once
#include <cstdint>

namespace core {
	class CoreApp {
	public:
		CoreApp();
		~CoreApp();

		void clear(uint32_t color);
		void update();
		uint32_t* getFramebuffer();
		int getWidth() const;
		int getHeight() const;
		void setWidth(int width);
		void setHeight(int height);

		static CoreApp* instance();

	private:
		struct Impl;
		Impl* d = nullptr;
	};
}
