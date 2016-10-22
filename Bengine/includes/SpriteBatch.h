
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Vertex.h"

#include <vector>
#include <algorithm>

namespace Engine {

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph {
	public:

		Glyph() {};
		Glyph(const glm::vec4& destinationRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& Color) : 
			texture(Texture), 
			depth(Depth) {

			topLeft.color = Color;
			topLeft.setPosition(destinationRect.x, destinationRect.y + destinationRect.w);
			topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

			bottomLeft.color = Color;
			bottomLeft.setPosition(destinationRect.x, destinationRect.y);
			bottomLeft.setUV(uvRect.x, uvRect.y);

			bottomRight.color = Color;
			bottomRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y);
			bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

			topRight.color = Color;
			topRight.setPosition(destinationRect.x + destinationRect.z, destinationRect.y + destinationRect.w);
			topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		};


		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	};

	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) { };

		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch {

	public:
		SpriteBatch();
		~SpriteBatch();

		void initBatch();

		void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void End();
		
		void Draw(const glm::vec4& destinationRect, const glm::vec4& uvRect, GLuint texture, float depth,  const ColorRGBA8& color);

		void renderbatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint m_vbo;
		GLuint m_vao;

		std::vector<Glyph*> m_pGlyphs; //Pointers for sorting
		std::vector<Glyph> m_glyphs; //Stack glyphs
		std::vector<RenderBatch> m_renderBatches;

		GlyphSortType m_sortType;

	};
}
#endif // !SPRITEBATCH_H