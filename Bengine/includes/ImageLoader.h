#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "../../includes/GL/glew.h"
#include "glTexture.h"
#include "ErrorSuite.h"


#include <string>
#include <iostream>

namespace Engine {
	class ImageLoader {

	public:

		//Load image (no GLTexture) from STB_Image
		static unsigned char* loadSTBImage(const std::string& filePath, int *width, int *height, int *bitsPerPixel, int forceBpp);

		//Create GLTexture from STBimage automatically
		static GLTexture loadImage(const std::string& filePath, int width, int height, int bitsPerPixel, int forceBpp);

		static void clearSTBImage(void *retval_from_stbi_load);

	};
}

#endif