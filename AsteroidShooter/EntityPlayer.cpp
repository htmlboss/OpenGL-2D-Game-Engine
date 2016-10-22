#include "includes\EntityPlayer.h"
#include "includes\EntityAsteroid.h"

#include <ResourceManager.h>
#include <InputManager.h>

#include <algorithm>


EntityPlayer::EntityPlayer(const int& BASE_ENTITY_WIDTH, const int& BASE_ENTITY_HEIGHT)
	: m_playerWidth(BASE_ENTITY_WIDTH + 31), m_playerHeight(BASE_ENTITY_HEIGHT + 85) {
}

EntityPlayer::~EntityPlayer() {
}

void EntityPlayer::Init(float speed, glm::vec2 position, Engine::InputManager* inputMgr) {

	m_speed = speed;
	m_position = position;
	m_inputMgr = inputMgr;

	//Setup bounding boxes

	//Center point
	Engine::Physics2D::UpdateAABB(m_playerBB, glm::dvec2(m_position.x + (m_playerWidth / 2), m_position.y + (m_playerHeight / 2)));
	//Half-widths
	m_playerBB.r = glm::dvec2((m_playerWidth / 2), (m_playerHeight / 2));
}

void EntityPlayer::Draw() {
	m_spritebatch.initBatch();
	m_spritebatch.Begin();

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 SpritePosition;
	//XY position of ship
	SpritePosition.x = m_position.x;
	SpritePosition.y = m_position.y;
	//Width/height of ship
	SpritePosition.z = m_playerWidth;
	SpritePosition.w = m_playerHeight;

	static int texID = Engine::ResourceManager::GetTexture("Data/textures/Player.png", 182, 356, 32, 4).id;

	m_spritebatch.Draw(SpritePosition, uvRect, texID, 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));

	m_spritebatch.End();
	m_spritebatch.renderbatch();
}

void EntityPlayer::Update(std::vector<std::shared_ptr<EntityAsteroid>>& asteroids, EntityPlayer& Player) {

	bool AABBneedsUpdate = false;

	//Check if we have any relevant input
	if (m_inputMgr->isKeyDown(SDLK_w) || 
		m_inputMgr->isKeyDown(SDLK_s) ||
		m_inputMgr->isKeyDown(SDLK_a) ||
		m_inputMgr->isKeyDown(SDLK_d)) {
		
		AABBneedsUpdate = true;
	}

	//Update positions
	if (m_inputMgr->isKeyDown(SDLK_w)) {
		m_position.y += m_speed;
	}
	else if (m_inputMgr->isKeyDown(SDLK_s)) {
		m_position.y -= m_speed;
	}

	if (m_inputMgr->isKeyDown(SDLK_a)) {
		m_position.x -= m_speed;
	}
	else if (m_inputMgr->isKeyDown(SDLK_d)) {
		m_position.x += m_speed;
	}

	//Update AABB's
	if (AABBneedsUpdate) {
		Engine::Physics2D::UpdateAABB(m_playerBB, glm::dvec2(m_position.x + (m_playerWidth / 2), m_position.y + (m_playerHeight / 2)));

		for (unsigned int i = 0; i < asteroids.size(); ++i) {
			auto collision = Engine::Physics2D::testAABB(m_playerBB, asteroids[i]->GetAsteroidAABB());
			if (std::get<0>(collision) == GL_TRUE) {

				std::cout << "\nCOLLISION DETECTED\n";
				m_position = Engine::Physics2D::ResolveCollision(collision, this->GetPosition(), this->GetPlayerAABB().r);
			}
		}
	}

}