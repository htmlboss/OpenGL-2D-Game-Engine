#ifndef TIMING_H
#define TIMING_H

#include <SDL\include\SDL.h>

namespace Engine {

	class LimitFPS {
	
	public:
		LimitFPS(const int& MaxFPS);
		void CalculateFPS();
		
		double const GetFps() const { return m_fps; }
		double GetMaxFPS() const { return m_maxFPS; }

	private:
		double m_maxFPS;
		double m_fps;
		double m_frameTime;
	};
}
#endif // !TIMING_H
