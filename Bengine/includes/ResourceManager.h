#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "TextureCache.h"

#include <string>

namespace Engine {
	class ResourceManager {

	public:

		static GLTexture GetTexture(const std::string& TexturePath, int texWidth, int texHeight, int bpp, int forceBPP);

	private:

		static TextureCache m_textureCache;
	};
}

#endif