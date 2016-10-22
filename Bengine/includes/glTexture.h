#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "../../includes/GL/glew.h"

namespace Engine {

	struct GLTexture {
		GLuint id;
		int width;
		int height;
	};
}

#endif