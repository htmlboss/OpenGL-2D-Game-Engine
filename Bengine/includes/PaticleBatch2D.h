#ifndef PARTICLE_BATCH_2D
#define PARTICLE_BATCH_2D

#include <glm/glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"

#include <memory>

namespace Engine {


	class Particle2D {
	public:
		friend class PaticleBatch2D;

		void Update(float DeltaTime);

	private:
		glm::vec2 m_position = glm::vec2(0.0f);
		glm::vec2 m_velocity = glm::vec2(0.0f);
		ColorRGBA8 m_color;
		float m_lifetime = 0.0f;
	};

	class PaticleBatch2D {

	public:
		PaticleBatch2D(int MaxParticles, float DecayRate);
		~PaticleBatch2D();

		void Init();
		void AddParticle(const glm::vec2& Position, const glm::vec2& Velocity, const ColorRGBA8& Color);
		void Update(float DeltaTime);
		void Draw();


	private:
		float m_decayRate = 0.1f;
		Particle2D* m_particles = nullptr;
		int m_maxParticles = 0;
	};
}
#endif // !PARTICLE_BATCH_2D