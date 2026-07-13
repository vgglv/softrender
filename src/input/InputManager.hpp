#pragma once

namespace input {
	enum class Key {
		W = 0,A,S,D
	};

	class InputManager {
	public:
		InputManager();
		~InputManager();
		static InputManager* instance();

		bool isKeyDown(const Key& k);
	};
}
