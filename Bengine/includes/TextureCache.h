#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <map>
#include <string>
#include <iostream>

#include "glTexture.h"
#include "ImageLoader.h"

namespace Engine {
	class TextureCache {
	public:

		TextureCache();
		~TextureCache();

		GLTexture GetTexture(const std::string& TexturePath, int texWidth, int texHeight, int bpp, int forceBPP);

	private:
		std::map<std::string, GLTexture> m_textureMap;
	};
}

#endif