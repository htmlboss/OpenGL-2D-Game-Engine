#include "ResourceManager.h"

namespace Engine {

	TextureCache ResourceManager::m_textureCache;

	GLTexture ResourceManager::GetTexture(const std::string& TexturePath, int texWidth, int texHeight, int bpp, int forceBPP) {

		return m_textureCache.GetTexture(TexturePath, texWidth, texHeight, bpp, forceBPP);
	}
}