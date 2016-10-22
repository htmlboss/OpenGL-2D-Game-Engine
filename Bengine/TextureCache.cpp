#include "TextureCache.h"

namespace Engine {

	TextureCache::TextureCache() {
	}

	TextureCache::~TextureCache() {
	}

	GLTexture TextureCache::GetTexture(const std::string& TexturePath, int texWidth, int texHeight, int bpp, int forceBPP) {

		// std::map<std::string, GLTexture>::iterator replaced with auto
		auto mitr = m_textureMap.find(TexturePath);

		if (mitr == m_textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadImage(TexturePath, texWidth, texHeight, bpp, forceBPP);

			m_textureMap.insert(make_pair(TexturePath, newTexture));

			return newTexture;
		}
		return mitr->second;
	}

}