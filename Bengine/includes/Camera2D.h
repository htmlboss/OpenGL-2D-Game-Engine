#ifndef CAMERA_2D
#define CAMERA_2D

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Engine {

	class Camera2D {
	public:
		Camera2D();
		~Camera2D();

		void init(double screenWidth, double screenHeight);

		void Update();

		bool isObjectinView(const glm::vec2& position, const glm::vec2& dimensions);

		//convert screen coordinates to world coordinates
		glm::vec2 screenToWorldCoords(glm::vec2 screenCoords);

		void setPosition(const glm::vec2& newPosition) {
			m_position = newPosition;
			m_needsMatUpdate = true;
		}
		void setScale(float newScale) {
			m_scale = newScale;
			m_needsMatUpdate = true;
		}

		//Helper function for position
		static glm::vec2 getPosition() { 
			return m_position;
		}
		
		float getScale() {
			return m_scale;
		}
		glm::mat4 getCameraMatrix() {
			return m_cameraMatrix;
		}

	private:

		bool m_needsMatUpdate;
		float m_scale;
		double m_screenWidth, m_screenHeight;
		
		static glm::vec2 m_position;
		
		glm::mat4 m_cameraMatrix;
		glm::mat4 m_orthoMatrix;
	};
}

#endif // !CAMERA_2D