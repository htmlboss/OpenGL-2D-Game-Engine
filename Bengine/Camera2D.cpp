#include "Camera2D.h"

namespace Engine {

	glm::vec2 Camera2D::m_position(0.0f);

	Camera2D::Camera2D() : m_needsMatUpdate(true), m_orthoMatrix(1.0f), m_scale(1.0f), m_cameraMatrix(1.0f), m_screenWidth(0), m_screenHeight(0) {
	}

	Camera2D::~Camera2D() {
	}

	void Camera2D::init(double screenWidth, double screenHeight) {
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		
		m_orthoMatrix = glm::ortho(0.0f, (static_cast<float>(m_screenWidth)), 0.0f, (static_cast<float>(m_screenHeight)));
	}

	void Camera2D::Update() {

		if (m_needsMatUpdate) {
			
			glm::vec3 translate(-m_position.x + m_screenWidth/2, -m_position.y + m_screenHeight/2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
			m_needsMatUpdate = false;
		}

	}

	bool Camera2D::isObjectinView(const glm::vec2& position, const glm::vec2& dimensions) {
		return true;
	}

	glm::vec2 Camera2D::screenToWorldCoords(glm::vec2 screenCoords) {
		//invert y-axis
		screenCoords.y = static_cast<float>(m_screenHeight) - screenCoords.y;
		//make (0,0) window center
		screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
		//scale coords
		screenCoords /= m_scale;
		//translate position
		screenCoords += m_position;
		
		return screenCoords;
	}
}