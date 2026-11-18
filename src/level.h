#ifndef PLAT_LEVEL_H_
#define PLAT_LEVEL_H_

#include <memory>

#include "actor.h"

namespace Plat {

class Level {
public:
	std::vector<std::shared_ptr<Actor>> actors;

	void Update(void);
};

} // namespace Plat

#endif // PLAT_LEVEL_H_
