#ifndef ENTITY_LASER_H
#define ENTITY_LASER_H


#include <EntityBase.h>
#include <SpriteBatch.h>
#include <Physics2D.h>

#include <memory>
#include <algorithm>

#include "EntityAsteroid.h"

class EntityLaser : public Engine::EntityBase {
public:
	EntityLaser(glm::vec2 Position, glm::vec2 Direction, float Speed, double Lifetime);
	~EntityLaser();

	void Draw();
	bool UpdateLaser(std::vector<std::shared_ptr<EntityAsteroid>>& asteroids);

private:
	float m_speed;
	glm::vec2 m_direction;
	glm::vec2 m_position;
	double m_lifetime;

	const glm::vec4 m_UV;

	Engine::SpriteBatch m_spritebatch;
	Engine::Physics2D::AABB2D m_laserBB;
};

#endif // !ENTITY_LASER_H