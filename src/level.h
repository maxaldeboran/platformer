#ifndef PLAT_LEVEL_H_
#define PLAT_LEVEL_H_

#include <memory>

#include <raylib.h>

#include "actor.h"

namespace Plat {

class Level {
public:
	std::list<std::shared_ptr<Actor>> actors;
	Vector2 gravity{0, 288*5}; /* reference constant acceleration */
	Vector2 wind{0, 0}; /* reference constant velocity */

	void Update(float dt);
};

} // namespace Plat

#endif // PLAT_LEVEL_H_
