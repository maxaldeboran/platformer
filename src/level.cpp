#include "level.h"

namespace Plat {

void Level::Update(float dt) {
	for (auto &actor : actors) {
		actor->Update(dt);
	}

	for (auto &solid : solids) {
		solid->Update(dt);
	}

	actors.remove_if([](std::shared_ptr<Actor> &a){ return a->ShouldDelete(); });
	solids.remove_if([](std::shared_ptr<Solid> &s){ return s->ShouldDelete(); });
}

} // namespace Plat
