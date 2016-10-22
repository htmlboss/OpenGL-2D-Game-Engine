
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <glm\glm.hpp>
//wrap input in enum class

namespace Engine
{
	class InputManager {
	public:

		InputManager();
		~InputManager();

		void update();

		void keyPressed(unsigned int keyID);
		void keyReleased(unsigned int keyID);

		void setMouseCoords(signed int x, signed int y);

		//Key held down
		bool isKeyDown(unsigned int keyID);

		//Key tapped
		bool isKeyPressed(unsigned int keyID);

		glm::vec2 getMouseCoords() const { return m_mouseCoords; }

	private:
		bool m_prevKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_prevKeyMap;

		glm::vec2 m_mouseCoords;
	};
}

#endif // !INPUTMANAGER_H