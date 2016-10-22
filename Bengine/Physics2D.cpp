#include "includes\Physics2D.h"

#include <iostream>
namespace Engine {

	void Engine::Physics2D::UpdateAABB(AABB2D & A, const glm::vec2 & newCenterPosition) {
		//Only center-points change
		A.c = glm::dvec2(newCenterPosition.x, newCenterPosition.y);
	}

	Physics2D::Collision Physics2D::testAABB(const AABB2D& A, const AABB2D& B) {
		//Check XY dimensions
		if (glm::abs(A.c[0] - B.c[0]) > (A.r[0] + B.r[0])) return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
		if (glm::abs(A.c[1] - B.c[1]) > (A.r[1] + B.r[1])) return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));

		else {
			glm::dvec2 halfWidths = B.r;
			// Get difference vector between both centers
			glm::dvec2 difference = B.c - A.c;
			glm::dvec2 clamped = glm::clamp(difference, -halfWidths, halfWidths);
			// Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
			glm::dvec2 closest = B.c + clamped;
			// Now retrieve vector between center circle and closest point AABB and check if length < radius
			difference = closest - A.c;

			//we have overlap
			return std::make_tuple(GL_TRUE, GetVectorDirection(difference), difference);
		}
	}

	glm::vec2 Physics2D::ResolveCollision(const Physics2D::Collision& collisionTuple, glm::vec2& position, const glm::dvec2& radius) {

		Direction dir = std::get<1>(collisionTuple);
		glm::dvec2 diffVector = std::get<2>(collisionTuple);
		
		//Horizontal collision
		if (dir == LEFT || dir == RIGHT) {
			//Relocate
			GLfloat penetration = radius.x - std::abs(diffVector.x);
			if (dir == LEFT) {
				position.x += penetration; //Move to the right
				std::cout << "Right";
			}
			else {
				position.x -= penetration; //Move to the left
				std::cout << "Left";
			}
		}
		//Vertical collision
		else {
			//Relocate
			GLfloat penetration = radius.y - std::abs(diffVector.y);
			if (dir == UP) {
				position.y -= penetration; //Move up
				std::cout << "UP";
			}
			else {
				position.y += penetration;
				std::cout << "Down";
			}
		}
		return position;
	}

	Physics2D::Direction Physics2D::GetVectorDirection(glm::dvec2& target) {
		glm::dvec2 compass[] = {
			glm::dvec2(0.0f, 1.0f),	// up
			glm::dvec2(1.0f, 0.0f),	// right
			glm::dvec2(0.0f, -1.0f),// down
			glm::dvec2(-1.0f, 0.0f)	// left
		};

		GLfloat max = 0.0f;
		GLuint best_match = -1;
		for (GLuint i = 0; i < 4; ++i) {
			
			GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
			
			if (dot_product > max) {
				max = dot_product;
				best_match = i;
			}
		}
		return static_cast<Direction>(best_match);
	}
}