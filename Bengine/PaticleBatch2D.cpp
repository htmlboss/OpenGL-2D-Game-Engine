#include "includes\PaticleBatch2D.h"


namespace Engine {

	///Particle2D
	void Particle2D::Update(float DeltaTime) {
		m_position += m_velocity;
	}

	///ParticleBatch2D
	PaticleBatch2D::PaticleBatch2D(int MaxParticles, float DecayRate) : m_maxParticles(MaxParticles), m_decayRate(DecayRate) {

	}

	PaticleBatch2D::~PaticleBatch2D() {
		delete[] m_particles;
	}

	void PaticleBatch2D::Init() {
		m_particles = new Particle2D[m_maxParticles];
	}

	void PaticleBatch2D::AddParticle(const glm::vec2& Position, const glm::vec2& Velocity, const ColorRGBA8& Color) {

	}
	 
	void PaticleBatch2D::Update(float DeltaTime) {
		for (unsigned int i = 0; i < m_maxParticles; ++i) {
			//Check if particle is active
			if (m_particles[i].m_lifetime > 0.0f) {
				m_particles[i].Update(DeltaTime);
				m_particles[i].m_lifetime -= m_decayRate * DeltaTime;
			}
		}
	}

	void PaticleBatch2D::Draw() {
	}
}