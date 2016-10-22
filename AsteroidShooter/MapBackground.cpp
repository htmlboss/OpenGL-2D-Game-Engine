#include "includes\MapBackground.h"

#include <ResourceManager.h>

MapBackground::MapBackground() {
}

MapBackground::~MapBackground() {
}

void MapBackground::Init(const std::string & BackgroundPath, Engine::InputManager* inputMgr, const glm::vec2& cameraPosition) {
	m_inputMgr = inputMgr;
	m_bgPath = BackgroundPath;
	m_position.x = cameraPosition.x - 500;
	m_position.y = cameraPosition.y - 1000;
}

void MapBackground::Update() {
		if (m_inputMgr->isKeyDown(SDLK_w)) {
			m_position.y += 0.075;
		}
		else if (m_inputMgr->isKeyDown(SDLK_s)) {
			m_position.y -= 0.075;
		}

		if (m_inputMgr->isKeyDown(SDLK_a)) {
			m_position.x += 0.075;
		}
		else if (m_inputMgr->isKeyDown(SDLK_d)) {
			m_position.x -= 0.075;
		}
}

void MapBackground::DrawBackground(Engine::SpriteBatch& spritebatch) {

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 position;
	//XY position of bg
	position.x = m_position.x;
	position.y = m_position.y;
	//Width/height of bg
	position.z = 3576;
	position.w = 2920;

	static int texID = Engine::ResourceManager::GetTexture(m_bgPath, 3576, 2920, 32, 4).id;

	spritebatch.Draw(position, uvRect, texID, 0.0f, Engine::ColorRGBA8(255, 255, 255, 255));
}
