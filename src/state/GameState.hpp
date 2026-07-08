#pragma once

namespace state {
	enum class GameState {
		TITLE_SCREEN = 0,
		TITLE_SCREEN_WAIT,
		MAIN_MENU_IN,
		MAIN_MENU,
		MAIN_MENU_OUT,
		GAME_SCENE
	};
}
