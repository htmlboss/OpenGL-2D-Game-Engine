#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "GL/glew.h"
#include "Vertex.h"
#include "glTexture.h"
#include "ResourceManager.h"

#include <cstddef>
#include <string>


namespace Engine {
	class Sprite {
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, const std::string& texturePath, int texWidth, int texHeight, int bpp, int forceBPP);

		void draw();

	private:
		float _x, _y, _width, _height;
		GLuint _vboID;

		GLTexture m_Texture;


	};
}

#endif // !SPRITE_H