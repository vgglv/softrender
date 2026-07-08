#pragma once

namespace scenes {
	class TitleScene {
	public:
		TitleScene();
		~TitleScene();

		void update(float dt);
	private:
		struct Impl;
		Impl* d = nullptr;
	};
}
