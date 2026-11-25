#include "level.h"

namespace Plat {

void Level::Update(float dt) {
	for (auto &actor : actors) {
		actor->Update(dt);
	}
}

} // namespace Plat
