#ifndef PLAT_GLOBALS_H_
#define PLAT_GLOBALS_H_

#include <memory>
#include <vector>

#include "resman.h"
#include "solid.h"
#include "level.h"

namespace Plat {

class Game {
public:
	ResMan resman;
	Level level;
};

extern Game *gGame;

} // namespace Plat

#endif // PLAT_GLOBALS_H_
