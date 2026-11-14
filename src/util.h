#ifndef PLAT_UTIL_H_
#define PLAT_UTIL_H_

constexpr float kEpsilon = 0.000001f;

constexpr int Sign(int x) {
	return (x > 0) - (x < 0);
}

constexpr int Sign(float x) {
	float eps = kEpsilon;
	return (x >= eps) - (x <= -eps);
}

struct IVector2 {
	int x, y;
};

#endif // PLAT_UTIL_H_
