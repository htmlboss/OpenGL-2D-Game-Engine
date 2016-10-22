#pragma once
#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL\include\SDL.h>
#include <GL\glew.h>

//Engine Deps
#include <Engine.h>
#include <GLSLProgram.h>
#include <Sprite.h>
#include <ErrorSuite.h>
#include <glTexture.h>
#include <Window.h>
#include <Camera2D.h>
#include <SpriteBatch.h>
#include <Vertex.h>
#include <InputManager.h>
#include <Timing.h>

#include <iostream>
#include <string>
#include <vector>

#include "Bullet.h"

enum class GameState {PLAY, EXIT};

class MainGame {
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	const int _screenWidth = 1600;
	const int _screenHeight = 900;
	float m_time;
	float m_maxFPS;
	double m_fps;

	GameState _gameState;

	Engine::Window _window;
	Engine::GLSLProgram _colorProgram;
	Engine::Camera2D m_Camera2D;
	Engine::SpriteBatch m_spriteBatch;
	Engine::InputManager m_inputMgr;
	Engine::LimitFPS m_limitFPS;

	std::vector<Bullet> m_bullets;

};

#endif