#include "level.h"

namespace Plat {

void Level::Update(void) {
	for (auto &actor : actors) {
		actor->Update();
	}
}

} // namespace Plat
