#include "includes/AsteroidShooter.h"

#include "Engine.h"

#include <iostream>


AsteroidShooter::AsteroidShooter() : m_gameState(GameState::LOADING), m_currentLevel(0), 
									 m_fps(0.0f), 
									 m_screenWidth(GetSystemMetrics(SM_CXSCREEN) / 1.5), 
									 m_screenHeight(GetSystemMetrics(SM_CYSCREEN) / 1.5),
									 m_player(ENTITY_BASE_WIDTH, ENTITY_BASE_HEIGHT),
									 m_framePerf(Engine::DisplayProps::REFRESHRATE){
	m_camera.init(m_screenWidth, m_screenHeight);
}

AsteroidShooter::~AsteroidShooter() {
}

void AsteroidShooter::Run() {

	initSystems();
	initLevel();
	gameLoop();
}

void AsteroidShooter::initSystems() {
	Engine::init();

	m_window.CreateNewWindow("Star Citizen", 0, "Data/textures/planets/planet_46.png");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Black



	initShaders();

	m_entitySpriteBatch.initBatch();
}

void AsteroidShooter::initShaders() {
	m_textureProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
}

void AsteroidShooter::initLevel() {
	m_levels.push_back(std::make_shared<Map>("Data/Level1.txt"));

	m_mapBackground.Init("Data/textures/electron-nebula.png", &m_inputManager, m_camera.getPosition());

	m_player.Init(1.5f, m_levels[m_currentLevel]->GetPlayerStartPos(), &m_inputManager);

	auto positions = m_levels[m_currentLevel]->GetAsteroidPositions();
	for (unsigned int i = 0; i < m_levels[m_currentLevel]->GetNumAsteroids(); i++) {
		m_asteroids.emplace_back(std::make_shared<EntityAsteroid>(positions[i], 60, 60));
	}
}

void AsteroidShooter::gameLoop() {

	m_gameState = GameState::PLAY;

	while (m_gameState == GameState::PLAY) {
		
		m_time += 0.01f;

		processInput();
		m_mapBackground.Update();
		m_player.Update(m_asteroids, m_player);

		for (unsigned int i = 0; i < m_lasers.size();) {
			if (m_lasers[i]->UpdateLaser(m_asteroids) == true) {
				m_lasers[i] = m_lasers.back();
				m_lasers.pop_back();
			}
			else {
				++i;
			}
		}

		//Camera tracks player
		auto p = m_player.GetPosition();
		m_camera.setPosition(glm::vec2(p.x, p.y + (m_screenHeight / 3)));
		m_camera.Update();
		
		//Draw the game
		drawGame();
		m_framePerf.CalculateFPS();

		static int frameCount = 0;
		frameCount++;
		if (frameCount == 20) {
			std::cout << m_framePerf.GetFps() << '\n';
			frameCount = 0;
		}
	}
}

void AsteroidShooter::processInput() {
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			// Exit the game here!
			m_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			m_inputManager.keyPressed(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.keyReleased(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.keyPressed(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.keyReleased(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		}

		//Mouse
		if (m_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords = m_camera.screenToWorldCoords(m_inputManager.getMouseCoords());
			//180 degree firing arc
			if (mouseCoords.y > (m_player.GetPosition().y + m_player.GetHeight())) {
				glm::vec2 laserOrigin = glm::vec2(m_player.GetPosition().x + (m_player.GetWidth() / 2), m_player.GetPosition().y + m_player.GetHeight());

				glm::vec2 direction = mouseCoords - laserOrigin;
				direction = glm::normalize(direction);

				m_lasers.emplace_back(std::make_shared<EntityLaser>(laserOrigin, direction, 5.0f, 1250.0f));
			}
		}
	}

	if (m_inputManager.isKeyDown(SDLK_ESCAPE)) {
		m_gameState = GameState::EXIT;
	}
}

void AsteroidShooter::drawGame() {

	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureProgram.use(1);

	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = m_textureProgram.getUniformLocation("spriteTexture");
	glUniform1i(textureUniform, 0);

	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();

	//Upload projection matrix
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &(projectionMatrix[0][0]));

	//Draw the shite
		//Backgorund
		m_entitySpriteBatch.Begin();
			m_mapBackground.DrawBackground(m_entitySpriteBatch);
		m_entitySpriteBatch.End();
		m_entitySpriteBatch.renderbatch();

		//Planets
		m_levels[m_currentLevel]->DrawPlanets();
		m_levels[m_currentLevel]->DrawSun(); //Sun will need separate shader

		//Entities
			//Lasers
			for (unsigned int i = 0; i < m_lasers.size(); ++i) {
				m_lasers[i]->Draw();
			}
			//Player
			m_player.Draw();
			//Asteroids
			for (unsigned int i = 0; i < m_asteroids.size(); ++i) {
				m_asteroids[i]->Draw();
			}

	m_textureProgram.unuse();

	// Swap our buffer and draw everything to the screen!
	m_window.SwapBuffers();
}