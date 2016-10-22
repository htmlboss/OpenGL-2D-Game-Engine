#ifndef MAP_BACKGROUND_H
#define MAP_BACKGROUND_H

#include <string>

#include <InputManager.h>
#include <SpriteBatch.h>

class MapBackground {
public:
	MapBackground();
	~MapBackground();

	void Init(const std::string& BackgroundPath, Engine::InputManager* inputMgr, const glm::vec2& cameraPosition);

	void Update();

	void DrawBackground(Engine::SpriteBatch& spritebatch);

private:

	std::string m_bgPath;
	Engine::InputManager* m_inputMgr;

	glm::vec2 m_position;
};

#endif // !MAP_BACKGROUND_H