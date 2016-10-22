#ifndef ASTEROID_SHOOTER_H
#define ASTEROID_SHOOTER_H

#include <memory>
#include <vector>

#include <SDL\include\SDL.h>
#include <GL\glew.h>
#include <InputManager.h>
#include <GLSLProgram.h>
#include <ErrorSuite.h>
#include <Window.h>
#include <Camera2D.h>
#include <SpriteBatch.h>
#include <InputManager.h>
#include <Timing.h>

#include <Windows.h>

#include "Map.h"
#include "EntityPlayer.h"
#include "EntityAsteroid.h"
#include "EntityLaser.h"
#include "MapBackground.h"

const int ENTITY_BASE_WIDTH = 60;
const int ENTITY_BASE_HEIGHT = 60;

enum class GameState { LOADING, PLAY, EXIT };

class AsteroidShooter {
public:
	AsteroidShooter();
	~AsteroidShooter();

	void Run();

private:

	void initSystems();
	void initShaders();
	void initLevel();

	/// Main game loop for the program
	void gameLoop();

	/// Handles input processing
	void processInput();

	/// Renders the game
	void drawGame();

	Engine::Window m_window;
	Engine::GLSLProgram m_textureProgram; ///< The shader program
	Engine::InputManager m_inputManager;
	Engine::Camera2D m_camera;
	Engine::SpriteBatch m_entitySpriteBatch;
	Engine::LimitFPS m_framePerf;

	std::vector<std::shared_ptr<Map>> m_levels; ///Levels
	std::vector<std::shared_ptr<EntityAsteroid>> m_asteroids; ///Asteroids
	std::vector<std::shared_ptr<EntityLaser>> m_lasers; ///Lasers

	EntityPlayer m_player;
	MapBackground m_mapBackground;
	GameState m_gameState;
	
	int m_currentLevel;
	double m_time;
	double m_fps;
	double m_frameTime;
	float m_screenWidth;
	float m_screenHeight;
};
#endif // !ASTEROID_SHOOTER_H