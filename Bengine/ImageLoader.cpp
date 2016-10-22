#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_FAILURE_USERMSG

namespace Engine {

	unsigned char* ImageLoader::loadSTBImage(const std::string& filePath, int *width, int *height, int *bitsPerPixel, int forceBpp = 4) {
		
		unsigned char *imageData = stbi_load(filePath.c_str(), width, height, bitsPerPixel, forceBpp);

		if (imageData == NULL) {
			const char *loadError = stbi_failure_reason();
			stbi_image_free(imageData);
			fatalError(loadError);
			loadError = NULL;
		}

		return imageData;
	}

	GLTexture ImageLoader::loadImage(const std::string& filePath, int width, int height, int bitsPerPixel, int forceBpp = 4) {
		GLTexture texture = {};

		unsigned char *imageData = loadSTBImage(filePath.c_str(), &width, &height, &bitsPerPixel, forceBpp);

		//Create the texture in opengl
		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imageData);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}

	void ImageLoader::clearSTBImage(void *retval_from_stbi_load) {
		stbi_image_free(retval_from_stbi_load);
	}
}