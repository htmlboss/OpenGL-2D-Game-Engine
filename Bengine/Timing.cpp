#include "includes\Timing.h"

namespace Engine {
	
	LimitFPS::LimitFPS(const int& MaxFPS) : m_maxFPS(MaxFPS) {
	}

	void LimitFPS::CalculateFPS() {
		static const int NUM_SAMPLES = 100;
		static double frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static uint32_t prevTicks = SDL_GetTicks();
		uint32_t currentTicks = SDL_GetTicks();

		m_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

		prevTicks = currentTicks;

		int count;

		currentFrame++;
		if (currentFrame < NUM_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUM_SAMPLES;
		}

		double frameTimeAvg = 0;
		for (unsigned int i = 0; i < count; ++i) {
			frameTimeAvg += frameTimes[i];
		}
		frameTimeAvg /= count;

		if (frameTimeAvg > 0) {
			m_fps = 1000.0f / frameTimeAvg;
		}
		else {
			m_fps = 999.0f;
		}
	}



}