#include "level.h"

namespace Plat {

void Level::Update(float dt) {
	for (auto &actor : actors) {
		actor->Update(dt);
	}

	for (auto it = actors.begin(); it != actors.end(); it++) {
		auto &actor = *it;
		if (actor->ShouldDelete()) {
			actors.erase(it);
		}
	}
}

} // namespace Plat
