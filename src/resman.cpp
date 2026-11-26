#include "resman.h"

namespace Plat {

Texture2D ResMan::GetTexture(std::string name)
{
	if (!EnsureTextureLoaded(name)) {
		return Texture2D{};
	}

	return *textureMap[name];
}

bool ResMan::EnsureTextureLoaded(std::string name)
{
	if (textureMap.contains(name)) {
		return true;
	}

	std::string path = "resources/textures/" + name + ".png";
	Texture2D texture = ::LoadTexture(path.c_str());
	int index = textures.size();
	textures.push_back(texture);
	textureMap[name] = &textures[index];

	return true;
}

} // namespace Plat
