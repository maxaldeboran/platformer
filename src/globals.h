#ifndef PLAT_GLOBALS_H_
#define PLAT_GLOBALS_H_

#include <vector>

#include "actor.h"

class Game {
public:
	std::vector<Solid> solids;
	std::vector<Actor> actors;
	Actor *player;
};

extern Game g_game;

#endif // PLAT_GLOBALS_H_
