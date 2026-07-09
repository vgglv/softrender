#pragma once

namespace scenes {
	class MainMenuScene {
	public:
		MainMenuScene();
		~MainMenuScene();

		void update(float dt);
	private:
		struct Impl;
		Impl* d = nullptr;
	};
}
