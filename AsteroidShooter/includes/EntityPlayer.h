#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include <EntityBase.h>
#include <Physics2D.h>
#include <InputManager.h>
#include <SpriteBatch.h>

#include <memory>
class EntityAsteroid;
class EntityPlayer : public Engine::EntityBase {
public:
	EntityPlayer(const int& BASE_ENTITY_WIDTH, const int& BASE_ENTITY_HEIGHT);
	~EntityPlayer();

	void Init(float speed, glm::vec2 position, Engine::InputManager* inputMgr);

	void Draw();

	void Update(std::vector<std::shared_ptr<EntityAsteroid>>& asteroids, EntityPlayer& Player);

	glm::vec2 GetPosition() const { return m_position; }
	double GetWidth() const { return m_playerWidth; }
	double GetHeight() const { return m_playerHeight; }
	Engine::Physics2D::AABB2D GetPlayerAABB() const { return m_playerBB; }

private:

	double m_playerWidth, m_playerHeight;

	//Player bounding box
	Engine::Physics2D::AABB2D m_playerBB;

	Engine::InputManager* m_inputMgr;
	Engine::SpriteBatch m_spritebatch;
};

#endif // !ENTITY_PLAYER_H