#include "InputManager.h"

namespace Engine {

	InputManager::InputManager() : m_mouseCoords(0.0f) {
	}

	InputManager::~InputManager() {
	}

	void InputManager::update() {

		//Loop through current keymap and copy it to m_prevKeyMap
		for (auto& it : m_keyMap) {
			m_prevKeyMap[it.first] = it.second;
		}
	}

	void InputManager::keyPressed(unsigned int keyID) {
		m_keyMap[keyID] = true;
	}

	void InputManager::keyReleased(unsigned int keyID) {
		m_keyMap[keyID] = false;
	}

	void InputManager::setMouseCoords(signed int x, signed int y) {
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;
	}

	bool InputManager::isKeyDown(unsigned int keyID) {
		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {

		if (isKeyDown(keyID) == true && m_prevKeyDown(keyID) == false) {
			return true;
		}
		else {
			return false;
		}
	}

	//Was key pressed last frame
	bool InputManager::m_prevKeyDown(unsigned int keyID) {

		auto it = m_keyMap.find(keyID);
		if (it != m_keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}
};