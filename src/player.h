#ifndef PLAT_PLAYER_H_
#define PLAT_PLAYER_H_

#include "actor.h"

namespace Plat {

class Player : public virtual Actor {
public:
	Player(void);
	void Update(void) override;
};

} // namespace Plat

#endif // PLAT_PLAYER_H_
