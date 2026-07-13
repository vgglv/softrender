#include "GameObject.hpp"

namespace {
	uint64_t lastIdx = 0;
}

namespace objects {
	GameObject::GameObject() : idx(++lastIdx) {}
}