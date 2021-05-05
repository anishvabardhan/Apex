#pragma once

#include <Windows.h>

namespace Apex {

	class Time
	{
		int m_FPS;
		LARGE_INTEGER m_Freq, m_DeltaTime, m_Start, m_End;
	public:
		Time(int fps);
		~Time();

		void InitGameTime(int fps);
		void Start();
		void End();
		float GetDeltaTime();

		void SetSeed();
	};

}