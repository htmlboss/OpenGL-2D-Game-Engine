#ifndef PHYSICS_2D
#define PHYSICS_2D

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <algorithm>
#include <tuple>

namespace Engine {

	class Physics2D {
	public:
		Physics2D() = delete;
		~Physics2D() = delete;

		// Represents the four possible (collision) directions
		enum Direction {UP, DOWN, RIGHT, LEFT};

		// Defines a Collision typedef that represents collision data
		typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

		//2D Axis Aligned Bounding Box
		//as per https://studiofreya.com/3d-math-and-physics/simple-aabb-vs-aabb-collision-detection/
		//Modified to use glm::dvec2 instead of Point
		typedef struct AABB2D {
			AABB2D() : c(), r() {}

			AABB2D(const glm::dvec2& Center, const glm::dvec2& halfwidths)
				: c(Center), r(halfwidths) {}

			glm::dvec2 c;	//center
			glm::dvec2 r;	//half-widths
		} AABB2D;

		///Functions
		//Update AABB center-point position
		static void UpdateAABB(AABB2D& A, const glm::vec2& newCenterPosition);

		//Test BB intersection between 2 AABBs
		static Collision testAABB(const AABB2D& A, const AABB2D& B);

		//Resolve Collisions
		static glm::vec2 ResolveCollision(const Physics2D::Collision& collisionTuple, glm::vec2& position, const glm::dvec2& radius);

		//Calculates which direction a vector is facing
		static Direction GetVectorDirection(glm::dvec2& target);

		//clamps a value to a value within a given range
		template<typename T>
		static void Clamp(const T& value, const T& min, const T& max) { return std::max(min, std::min(max, value)); }
	};
}

#endif // !PHYSICS_2D