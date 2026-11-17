#ifndef PLAT_GLOBALS_H_
#define PLAT_GLOBALS_H_

#include <vector>

#include "actor.h"

namespace Plat {

extern std::vector<Solid> solids;
extern std::vector<Actor> actors;
extern Actor *player;

}

#endif // PLAT_GLOBALS_H_
