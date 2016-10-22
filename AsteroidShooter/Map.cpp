#include "includes/Map.h"

#include <ErrorSuite.h>
#include <ResourceManager.h>

#include <fstream>
#include <iostream>


Map::Map(const std::string& mapDataPath) : m_uvRect(0.0f, 0.0f, 1.0f, 1.0f){

	std::ifstream file;
	file.open(mapDataPath);

	if (file.fail()) {
		Engine::fatalError("Failed to open " + mapDataPath);
	}

	//Get number of asteroids
	std::string temp;
	file >> temp >> m_numAsteroids;

	//store file lines in map vector
	while (std::getline(file, temp)) {
		m_mapData.push_back(temp);
	}

/*//Print out map in console
#ifdef _DEBUG
	for (unsigned int i = 0; i < m_mapData.size(); i++) {
		std::cout << m_mapData[i] << std::endl;
	}
#endif // _DEBUG
*/

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	//Render tiles
	for (unsigned int y = 0; y < m_mapData.size(); y++) {
		for (unsigned int x = 0; x < m_mapData[y].size(); x++) {
			//Grab tile
			char tile = m_mapData[y][x];
			//Parse tile
			switch (tile) {
			//Planet 1 (Earth-like)
			case '1':
				m_planet1 = glm::vec4(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH * 15, TILE_WIDTH * 15);
				break;

			//Planet 2 (Moon)
			case '2':
				m_planet2 = glm::vec4(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH * 5, TILE_WIDTH * 5);
				break;

			//Planet 3 (Gas Giant)
			case '3':
				m_planet3 = glm::vec4(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH * 25, TILE_WIDTH * 25);
				break;

			//Sun
			case 'S':
				m_sun = glm::vec4(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH * 45, TILE_WIDTH * 45);
				break;

			//Player
			case '@':
				m_playerStartPos.x = x * TILE_WIDTH;
				m_playerStartPos.y = y * TILE_WIDTH;
				m_mapData[y][x] = '.'; //Don't collide with start position
				break;

			//Asteroids
			case 'A':
				m_asteroidPositions.push_back(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH));
				break;

			//Map Boundaries
			case '-':
				break;

			//Ignore periods
			case '.':
				break;

			default:
				std::printf("\nUnexpected Symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}
	}

}

Map::~Map() {
}

void Map::DrawMap() {
	m_spriteBatch.renderbatch();
}

void Map::DrawPlanets() {
	m_spriteBatch.initBatch();
	m_spriteBatch.Begin();

	//Planet 1 (Earth-like)
	m_spriteBatch.Draw(m_planet1,
		m_uvRect,
		Engine::ResourceManager::GetTexture("Data/textures/planets/planet_46.png", 500, 500, 32, 4).id,
		0.0f,
		Engine::ColorRGBA8(255, 255, 255, 255)
	);

	//Planet 2 (Moon)
	m_spriteBatch.Draw(m_planet2,
		m_uvRect,
		Engine::ResourceManager::GetTexture("Data/textures/planets/planet_37.png", 500, 500, 32, 4).id,
		0.0f,
		Engine::ColorRGBA8(255, 255, 255, 255)
	);

	//Planet 3 (Gas Giant)
	m_spriteBatch.Draw(m_planet3,
		m_uvRect,
		Engine::ResourceManager::GetTexture("Data/textures/planets/planet_48.png", 500, 500, 32, 4).id,
		0.0f,
		Engine::ColorRGBA8(255, 255, 255, 255)
	);

	m_spriteBatch.End();

	m_spriteBatch.renderbatch();
}

void Map::DrawSun() {
	m_spriteBatch.initBatch();
	m_spriteBatch.Begin();

	m_spriteBatch.Draw(m_sun,
		m_uvRect,
		Engine::ResourceManager::GetTexture("Data/textures/planets/Sun.png", 521, 522, 32, 4).id,
		0.0f,
		Engine::ColorRGBA8(255, 255, 255, 255)
	);

	m_spriteBatch.End();

	m_spriteBatch.renderbatch();
}
