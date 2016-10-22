#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include <glm\glm.hpp>

#include <GLSLProgram.h>
#include <SpriteBatch.h>
#include <ResourceManager.h>

#include <string>

namespace Engine {
	
	class EntityBase {
	public:
		EntityBase();
		virtual ~EntityBase();

		virtual void Draw() = 0;

		virtual void Update();

	protected:
		///Variables
		glm::vec2 m_position;
		glm::vec4 m_posAndSize;

		double m_speed;


	};
}
#endif // !ENTITY_BASE_H