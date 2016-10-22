#include "Sprite.h"

namespace Engine {

	Sprite::Sprite() : _vboID(0) {
	}

	Sprite::~Sprite() {
		//Always remember to delete your buffers when
		//you are done!
		if (_vboID != 0) {
			glDeleteBuffers(1, &_vboID);
		}
	}

	//Initializes the sprite VBO. x, y, width, and height are
	//in the normalized device coordinate space. so, [-1, 1]
	void Sprite::init(float x, float y, float width, float height, const std::string& texturePath, int texWidth, int texHeight, int bpp, int forceBPP) {
		//Set up our private vars
		_x = x;
		_y = y;
		_width = width;
		_height = height;


		m_Texture = ResourceManager::GetTexture(texturePath, texWidth, texHeight, bpp, forceBPP);


		//Generate the buffer if it hasn't already been generated
		if (_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		//First Triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		//Tell opengl to bind our vertex buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//Upload the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		//Unbind the buffer (optional)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//Draws the sprite to the screen
	void Sprite::draw() {

		glBindTexture(GL_TEXTURE_2D, m_Texture.id);

		//bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);


		//Draw the 6 vertices to the screen
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//Disable the vertex attrib array.
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		//Unbind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}