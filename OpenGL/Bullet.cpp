#include "includes\Bullet.h"


Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifetime) {
	m_position = position;
	m_direction = direction;
	m_speed = speed;
	m_lifetime = lifetime;
}

Bullet::~Bullet() {
}

void Bullet::draw(Engine::SpriteBatch & spriteBatch) {

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Engine::GLTexture texture = Engine::ResourceManager::GetTexture("assets/textures/PNG/CharacterRight_Standing.png", 73, 79, 32, 4);
	auto color = Engine::ColorRGBA8(255, 255, 255, 255);

	glm::vec4 posAndSize = glm::vec4(m_position.x, m_position.y, 30, 30);

	spriteBatch.Draw(posAndSize, uv, texture.id, 0.0f, color);

}

bool Bullet::update() {
	m_position += m_direction * m_speed;
	m_lifetime--;
	if (m_lifetime == 0) {
		return true;
	}
	return false;
}