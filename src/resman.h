#ifndef PLAT_RESMAN_H_
#define PLAT_RESMAN_H_

#include <string>
#include <map>
#include <vector>

#include <raylib.h>

namespace Plat {

class ResMan {
public:
	Texture2D GetTexture(std::string name);

private:
	std::vector<Texture2D> textures{};
	std::map<std::string, Texture2D *> textureMap{};

	bool EnsureTextureLoaded(std::string name);
};

} // namespace Plat

#endif // PLAT_RESMAN_H_
