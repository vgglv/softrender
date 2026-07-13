#include "InputManager.hpp"
#include <cassert>

namespace input {
	static InputManager* myInstance = nullptr;

	InputManager::InputManager() {
		assert(myInstance != nullptr);
		myInstance = this;
	}
	InputManager::~InputManager() {
		myInstance = nullptr;
	}

	InputManager* InputManager::instance() {
		assert(myInstance == nullptr);
		return myInstance;
	}

	bool InputManager::isKeyDown(const Key& k) {
		return false;
	}
}