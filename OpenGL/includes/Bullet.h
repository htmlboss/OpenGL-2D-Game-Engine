#ifndef BULLET_H
#define BULLET_H

#include <glm\glm.hpp>
#include <SpriteBatch.h>
#include <ResourceManager.h>


class Bullet {
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifetime);
	~Bullet();

	void draw(Engine::SpriteBatch& spriteBatch);
	bool update();

private:
	float m_speed;
	glm::vec2 m_direction;
	glm::vec2 m_position;
	int m_lifetime;

};

#endif // !BULLET_H