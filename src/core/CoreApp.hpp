#pragma once

#include <vector>
namespace core {
	class CoreApp {
	public:
		CoreApp();
		~CoreApp();

		void clear(uint32_t color);
		void render();
		uint32_t* getFramebuffer();
		int getWidth() const;
		int getHeight() const;
		void setWidth(int width);
		void setHeight(int height);

		static CoreApp* instance();

	private:
		int _width;
		int _height;

		//AARRGGBB
		std::vector<uint32_t> _framebufferVector;
	};
}
