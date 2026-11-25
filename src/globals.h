#ifndef PLAT_GLOBALS_H_
#define PLAT_GLOBALS_H_

#include <memory>
#include <vector>

#include "solid.h"
#include "level.h"

namespace Plat {

class Game {
public:
	Level level;
	std::list<std::shared_ptr<Solid>> solids;
};

extern Game *gGame;

} // namespace Plat

#endif // PLAT_GLOBALS_H_
