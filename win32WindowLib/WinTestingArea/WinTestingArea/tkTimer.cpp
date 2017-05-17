#include "tkTimer.h"
#include <Windows.h>

namespace tk {
	Timer::Timer() : m_running(false), m_startTime(0) {
		LARGE_INTEGER ticksPerSec;
		m_isHighPerformance = QueryPerformanceFrequency(&ticksPerSec) == TRUE;
		m_frequency = 1.0 / (m_isHighPerformance ? ticksPerSec.QuadPart : 1000);
	}

	double tk::Timer::elapsed() const {
		if (m_running) {
			LONGLONG now;
			if (m_isHighPerformance) {
				LARGE_INTEGER qwTime;
				QueryPerformanceCounter(&qwTime);
				now = qwTime.QuadPart;
			}
			else {
				now = GetTickCount();
			}
			return (now - m_startTime) * m_frequency;
		}
		else {
			return 0.0;
		}
	}


	bool tk::Timer::running() const {
		return m_running;
	}

	void tk::Timer::start() {
		m_running = true;

		if (m_isHighPerformance) {
			LARGE_INTEGER qwTime;
			QueryPerformanceCounter(&qwTime);
			m_startTime = qwTime.QuadPart;
		}
		else {
			m_startTime = GetTickCount();
		}
	}

	void tk::Timer::stop() {
		m_running = false;
	}

}