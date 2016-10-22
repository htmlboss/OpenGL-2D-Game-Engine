#ifndef VERTEX_H
#define VERTEX_H

#include <GL\glew.h>

namespace Engine {
	struct Position {
		//Default to Origin
		Position() : x(0), y(0) {};
		Position(float X, float Y) : x(X), y(Y) {};

		float x;
		float y;
	};

	struct ColorRGBA8 {
		//Default to black
		ColorRGBA8() : r(0), g(0), b(0), a(1) {};
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R),
																 g(G),
																 b(B),
																 a(A) {};
		
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		UV() : u(0), v(0) {};
		UV(float U, float V) : u(U), v(V) {};

		float u;
		float v;
	};

	struct Vertex {

		Position position;
		ColorRGBA8 color;
		UV uv;

		void setPosition(float x, float y) {
			position = Position(x, y);
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color = ColorRGBA8(r, g, b, a);
		}

		void setUV(float u, float v) {
			uv = UV(u, v);
		}
	};
}

#endif // !VERTEX_H
