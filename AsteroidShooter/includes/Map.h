#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <memory>

#include <SpriteBatch.h>
#include <ResourceManager.h>

const int TILE_WIDTH = 16;

class Map {
public:
	Map(const std::string& mapDataPath);
	~Map();

	void DrawMap();
	void DrawPlanets();
	void DrawSun();

	glm::vec2 GetPlayerStartPos() const { return m_playerStartPos; }

	const std::vector<std::string>& GetLevelData() const { return m_mapData; }
	const std::vector<glm::vec2>& GetAsteroidPositions() const { return m_asteroidPositions; }
	const int GetNumAsteroids() const { return m_numAsteroids; }

private:

	std::vector<std::string> m_mapData;
	std::vector<glm::vec2> m_asteroidPositions;

	glm::vec4 m_sun, m_planet1, m_planet2, m_planet3;
	glm::vec2 m_playerStartPos;

	const glm::vec4 m_uvRect;

	int m_numAsteroids;

	Engine::SpriteBatch m_spriteBatch;

};

#endif // !MAP_H