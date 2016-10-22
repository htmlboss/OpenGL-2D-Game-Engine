#ifndef ENTITY_ASTEROID_H
#define ENTITY_ASTEROID_H

#include <Physics2D.h>
#include <EntityBase.h>
#include <SpriteBatch.h>

class EntityAsteroid : public Engine::EntityBase {
public:
	EntityAsteroid(const glm::vec2& Position, const int& BASE_ENTITY_WIDTH, const int& BASE_ENTITY_HEIGHT);
	~EntityAsteroid();

	void Draw();

	void Update(std::vector<EntityAsteroid>& asteroids);

	Engine::Physics2D::AABB2D GetAsteroidAABB() const { return m_asteroidBB; }
	glm::vec2 GetPosition() const { return m_position; }

	double GetWidth() const { return m_width; }
	double GetHeight() const { return m_height; }

private:

	double m_width, m_height;

	glm::vec2 m_position;

	Engine::Physics2D::AABB2D m_asteroidBB;

	Engine::SpriteBatch m_spritebatch;
};

#endif // !ENTITY_ASTEROID_H