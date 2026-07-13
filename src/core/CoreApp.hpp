#pragma once

namespace core {
	class CoreApp {
	public:
		CoreApp(int width, int height);
		~CoreApp();

		void update();
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
