#include "Time.h"

namespace Apex {

	Time::Time(int fps)
		:m_FPS(fps)
	{
		InitGameTime(m_FPS);
	}

	Time::~Time()
	{
	}

	void Time::InitGameTime(int fps)
	{
		QueryPerformanceFrequency(&m_Freq);
		m_DeltaTime.QuadPart = fps;
	}

	void Time::Start()
	{
		QueryPerformanceCounter(&m_Start);
	}

	void Time::End()
	{
		QueryPerformanceCounter(&m_End);

		m_DeltaTime.QuadPart = (m_End.QuadPart - m_Start.QuadPart) * 1000000;
		m_DeltaTime.QuadPart /= m_Freq.QuadPart;

		if (m_DeltaTime.QuadPart > m_FPS)
			m_DeltaTime.QuadPart = (LONGLONG)m_FPS;
	}

	float Time::GetDeltaTime()
	{
		return 1.0f / (float)m_DeltaTime.QuadPart;
	}

}