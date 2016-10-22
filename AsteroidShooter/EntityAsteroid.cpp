#include "includes\EntityAsteroid.h"

#include <ResourceManager.h>

EntityAsteroid::EntityAsteroid(const glm::vec2& Position, const int& BASE_ENTITY_WIDTH, const int& BASE_ENTITY_HEIGHT) 
	: m_width(BASE_ENTITY_WIDTH + 15), m_height(BASE_ENTITY_HEIGHT + 14), m_position(Position) {
	
	double posX = m_position.x + (m_width / 2);
	double posY = m_position.y + (m_height / 2);
	m_asteroidBB.c = glm::dvec2(posX, posY);
	
	m_asteroidBB.r = glm::dvec2(m_width / 2, m_height / 2);


	m_spritebatch.initBatch();
	m_spritebatch.Begin();

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 position;
	//XY position of asteroid
	position.x = m_position.x;
	position.y = m_position.y;
	//Width/height of asteroid
	position.z = m_width;
	position.w = m_height;

	static int texID = Engine::ResourceManager::GetTexture("Data/textures/asteroids/1.png", 99, 96, 32, 4).id;

	m_spritebatch.Draw(position, uvRect, texID, 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_spritebatch.End();
}

EntityAsteroid::~EntityAsteroid() {
}

void EntityAsteroid::Draw() {
	m_spritebatch.renderbatch();
}
void EntityAsteroid::Update(std::vector<EntityAsteroid>& asteroids) {
}