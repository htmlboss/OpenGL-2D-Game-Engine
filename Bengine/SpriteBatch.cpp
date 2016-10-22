#include "SpriteBatch.h"

namespace Engine {

	SpriteBatch::SpriteBatch() : m_vao(0), m_vbo(0) {
	}

	SpriteBatch::~SpriteBatch() {
	}

	void SpriteBatch::initBatch() {
		createVertexArray();
	}

	void SpriteBatch::Begin(GlyphSortType sortType /*GlyphSortType::TEXTURE*/) {
		m_sortType = sortType;
		m_renderBatches.clear();
		
		m_glyphs.clear();
	}
	
	void SpriteBatch::End() {

		//Setup glyph pointers for fast sorting
		m_pGlyphs.resize(m_glyphs.size());
		for (int i = 0; i < m_glyphs.size(); i++) {
			//Assign memory address of stack glyphs to pointers
			m_pGlyphs[i] = &m_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::Draw(const glm::vec4& destinationRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color) {

		m_glyphs.emplace_back(destinationRect, uvRect, texture, depth, color);

	}

	void SpriteBatch::createRenderBatches() {
		
		//Stores all vertices for upload
		std::vector<Vertex> vertices;
		//reserve memory for vector
		vertices.resize(m_pGlyphs.size() * 6);
		
		if (m_pGlyphs.empty()) {
			return;
		}

		int cv = 0, offst = 0; //current vertex, offset
		m_renderBatches.emplace_back(offst, 6, m_pGlyphs[0]->texture);
		vertices[cv++] = m_pGlyphs[0]->topLeft;
		vertices[cv++] = m_pGlyphs[0]->bottomLeft;
		vertices[cv++] = m_pGlyphs[0]->bottomRight;
		vertices[cv++] = m_pGlyphs[0]->bottomRight;
		vertices[cv++] = m_pGlyphs[0]->topRight;
		vertices[cv++] = m_pGlyphs[0]->topLeft;
		offst += 6;
		
		//Add all the rest of the glyphs
		for (unsigned int cg = 1; cg < m_pGlyphs.size(); cg++) {
			
			if (m_pGlyphs[cg]->texture != m_pGlyphs[cg - 1]->texture) {
				m_renderBatches.emplace_back(offst, 6, m_pGlyphs[cg]->texture);
			}
			else {
				m_renderBatches.back().numVertices += 6;
			}
			
			vertices[cv++] = m_pGlyphs[cg]->topLeft;
			vertices[cv++] = m_pGlyphs[cg]->bottomLeft;
			vertices[cv++] = m_pGlyphs[cg]->bottomRight;
			vertices[cv++] = m_pGlyphs[cg]->bottomRight;
			vertices[cv++] = m_pGlyphs[cg]->topRight;
			vertices[cv++] = m_pGlyphs[cg]->topLeft;
			offst += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray() {

		if (m_vao == 0) {
			glGenVertexArrays(1, &m_vao);
		}
		glBindVertexArray(m_vao);


		if (m_vbo == 0) {
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Position pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//color pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//UV pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//unbind vbo
		glBindVertexArray(0);

	}

	void SpriteBatch::sortGlyphs() {

		switch (m_sortType) {

		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_pGlyphs.begin(), m_pGlyphs.end(), compareTexture);
			break;
		}
		
	}

	bool SpriteBatch::compareFrontToBack(Glyph* A, Glyph* B) {
		return (A->depth < B->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph* A, Glyph* B) {
		return (A->depth > B->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* A, Glyph* B) {
		return (A->texture < B->texture);
	}

	void SpriteBatch::renderbatch() {

		glBindVertexArray(m_vao);

		for (unsigned int i = 0; i < m_renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}
}