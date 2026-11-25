#include "level.h"

namespace Plat {

void Level::Update(float dt) {
	for (auto &actor : actors) {
		actor->Update(dt);
	}

	actors.remove_if([](std::shared_ptr<Actor> &a){ return a->ShouldDelete(); });
}

} // namespace Plat
