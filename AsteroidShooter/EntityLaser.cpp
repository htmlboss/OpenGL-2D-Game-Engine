#include "includes\EntityLaser.h"

EntityLaser::EntityLaser(glm::vec2 Position, glm::vec2 Direction, float Speed, double Lifetime) : m_position(Position), 
																								  m_direction(Direction), 
																								  m_speed(Speed), m_lifetime(Lifetime),
																								  m_UV(0.0f, 0.0f, 1.0f, 1.0f)
																								  {
	m_laserBB.c = glm::dvec2(m_position.x + 7.0f, m_position.y + 8.5f);
	m_laserBB.r = glm::dvec2(7.0f, 8.5f);
}

EntityLaser::~EntityLaser() {
}

void EntityLaser::Draw() {
	m_spritebatch.initBatch();
	m_spritebatch.Begin();

	auto textureID = Engine::ResourceManager::GetTexture("Data/textures/laser.png", 14, 17, 32, 4).id;

	m_spritebatch.Draw(glm::vec4(m_position.x, m_position.y, 14, 17), m_UV, textureID, 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_spritebatch.End();
	m_spritebatch.renderbatch();
}

bool EntityLaser::UpdateLaser(std::vector<std::shared_ptr<EntityAsteroid>>& asteroids) {
	this->m_position += this->m_direction * m_speed;
	
	//Check AABB after position change
	Engine::Physics2D::UpdateAABB(m_laserBB, m_position);

	for (unsigned int i = 0; i < asteroids.size(); ++i) {
		auto collision = Engine::Physics2D::testAABB(this->m_laserBB, asteroids[i]->GetAsteroidAABB());

		//Test for collision and handle it
		if (std::get<0>(collision) == GL_TRUE) {

			//Despawn laser
			this->m_lifetime = 0;
			
			//Swap colliding asteroid to the end of asteroid vector
			if (!asteroids.empty()) {
				std::swap(asteroids[i], asteroids.back());
				//Remove asteroid
				asteroids.pop_back();
			}

			return true;
		}
		else {
			this->m_lifetime--;

			if (this->m_lifetime == 0) {
				return true;
			}
		}
	}

	return false;
}
