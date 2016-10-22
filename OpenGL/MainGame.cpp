#include "includes\MainGame.h"

using namespace Engine;

MainGame::MainGame() : m_time(0.0f), _gameState(GameState::PLAY), m_maxFPS(60.0f) {
	m_Camera2D.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame() {
}

void MainGame::run() {
	initSystems();

	//This only returns when the game ends
	gameLoop();
}

void MainGame::initSystems() {

	_window.CreateNewWindow("Game Engine", 0, "");

	initShaders();
	m_spriteBatch.initBatch();
	m_limitFPS.init(m_maxFPS);
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {

	//Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT) {
		
		m_limitFPS.BeginFrame();

		m_inputMgr.update();

		processInput();
		m_time += 0.01f;

		m_Camera2D.Update();

		//updates bullets
		for (unsigned int i = 0; i < m_bullets.size();) {
			if (m_bullets[i].update() == true) {
				m_bullets[i] = m_bullets.back();
				m_bullets.pop_back();
			}
			else {
				i++;
			}
		}


		drawGame();
		
		m_fps = m_limitFPS.End();
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 1000) {
			std::cout << m_fps << std::endl;
			frameCounter = 0;
		}
		
	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				m_inputMgr.keyPressed(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_inputMgr.keyReleased(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_inputMgr.keyPressed(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_inputMgr.keyReleased(evnt.button.button);
				break;
			case SDL_MOUSEMOTION:
				m_inputMgr.setMouseCoords(evnt.motion.x, evnt.motion.y);
				break;
		}
		if (m_inputMgr.isKeyDown(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords = m_inputMgr.getMouseCoords();
			mouseCoords = m_Camera2D.screenToWorldCoords(mouseCoords);
			
			glm::vec2 playerPosition(0.0f);
			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);

			m_bullets.emplace_back(playerPosition, direction, 4.0f, 1000);
		}
	}
	if (m_inputMgr.isKeyDown(SDLK_ESCAPE)) {
		_gameState = GameState::EXIT;
	}
	if (m_inputMgr.isKeyDown(SDLK_w)) {
		m_Camera2D.setPosition(m_Camera2D.getPosition() + glm::vec2(0.0f, 2.0f));
	}
	if (m_inputMgr.isKeyDown(SDLK_s)) {
		m_Camera2D.setPosition(m_Camera2D.getPosition() + glm::vec2(0.0f, -2.0f));
	}
	if (m_inputMgr.isKeyDown(SDLK_a)) {
		m_Camera2D.setPosition(m_Camera2D.getPosition() + glm::vec2(-2.0f, 0.0f));
	}
	if (m_inputMgr.isKeyDown(SDLK_d)) {
		m_Camera2D.setPosition(m_Camera2D.getPosition() + glm::vec2(2.0f, 0.0f));
	}
	if (m_inputMgr.isKeyDown(SDLK_q)) {
		m_Camera2D.setScale(m_Camera2D.getScale() + 0.5);
	}
	if (m_inputMgr.isKeyDown(SDLK_e)) {
		m_Camera2D.setScale(m_Camera2D.getScale() + -0.5);
	}
	if (m_inputMgr.isKeyDown(SDLK_SPACE)) {
		m_Camera2D.setPosition(glm::vec2(0.0f, 0.0f));
		m_Camera2D.setScale(1.0f);
	}
}

void MainGame::drawGame() {
	//Set the base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//use the shaders
	_colorProgram.use(1);

	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.getUniformLocation("spriteTexture");
	glUniform1i(textureLocation, 0);

	//Set camera matrix
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_Camera2D.getCameraMatrix();

	//upload matrix to gpu
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//sprite batching
	m_spriteBatch.Begin();

	glm::vec4 position(0.0f, 0.0f, 50, 50);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GLTexture texture = ResourceManager::GetTexture("assets/textures/PNG/CharacterRight_Standing.png", 73, 79, 32, 4);
	ColorRGBA8 color = ColorRGBA8(255, 255, 255, 255);

	//sprite draw calls
	m_spriteBatch.Draw(position, uv, texture.id, 0.0f, color);

	for (unsigned int i = 0; i < m_bullets.size(); i++) {
		m_bullets[i].draw(m_spriteBatch);
	}

	m_spriteBatch.End();
	m_spriteBatch.renderbatch();
	

	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.unuse();

	_window.SwapBuffers();

}