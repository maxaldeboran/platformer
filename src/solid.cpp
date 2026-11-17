#include "solid.h"

#include <cmath>

#include "globals.h"

void Solid::Move(float amountX, float amountY)
{
	xRemainder += amountX;
	yRemainder += amountY;
	int moveX = roundf(xRemainder);
	int moveY = roundf(yRemainder);

	if (moveX == 0 && moveY == 0) {
		return;
	}

	for (auto &actor : g_game.actors) {
		actor.isRidingCurrent = actor.IsRiding(*this);
	}

	isCollidable = false;

	xRemainder -= moveX;
	position.x += moveX;

	if (moveX > 0) {
		for (auto &actor : g_game.actors) {
			if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
				bool hit = actor.MoveX(hiX() - actor.loX() + 1);
				if (hit) actor.Squish();
			} else if (actor.isRidingCurrent) {
				actor.MoveX(moveX);
			}
		}
	} else if (moveX < 0) {
		for (auto &actor : g_game.actors) {
			if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
				bool hit = actor.MoveX(loX() - actor.hiX() - 1);
				if (hit) actor.Squish();
			} else if (actor.isRidingCurrent) {
				actor.MoveX(moveX);
			}
		}
	}

	yRemainder -= moveY;
	position.y += moveY;

	if (moveY > 0) {
		for (auto &actor : g_game.actors) {
			if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
				bool hit = actor.MoveY(hiY() - actor.loY() + 1);
				if (hit) actor.Squish();
			} else if (actor.isRidingCurrent) {
				actor.MoveY(moveY);
			}
		}
	} else if (moveY < 0) {
		for (auto &actor : g_game.actors) {
			if (AabbsOverlap(GetHitboxTranslated(), actor.GetHitboxTranslated())) {
				bool hit = actor.MoveY(loY() - actor.hiY() - 1);
				if (hit) actor.Squish();
			} else if (actor.isRidingCurrent) {
				actor.MoveY(moveY);
			}
		}
	}

	isCollidable = true;
}
