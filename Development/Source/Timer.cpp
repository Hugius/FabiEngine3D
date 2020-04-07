#include <WE3D/Timer.hpp>
	
void Timer::setCustomDeltaTime(float delta)
{
	p_deltaTime = delta;
}

void Timer::calculateDeltaTime()
{
	p_deltaTime = 0.0f;

	for (auto& element : p_deltaParts)
	{
		p_deltaTime += element.second;
	}
}

// Start measuring time
void Timer::start(const string& ID)
{
	QueryPerformanceFrequency(&p_frequency);
	QueryPerformanceCounter(&p_time1);
	p_currentID = ID;
}

// Calculate the delta time
void Timer::stop()
{
	QueryPerformanceCounter(&p_time2);
	p_deltaParts[p_currentID] = static_cast<float>((p_time2.QuadPart - p_time1.QuadPart) * 1000.0f / p_frequency.QuadPart);
}

float Timer::getDeltaPart(const string& ID)
{
	return p_deltaParts[ID];
}

float Timer::getDeltaTime()
{
	return p_deltaTime;
}

void Timer::uSleep(int waitTime)
{
	__int64 time1 = 0, time2 = 0, freq = 0;

	QueryPerformanceCounter((LARGE_INTEGER *)&time1);
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

	do 
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&time2);
	} 
	while ((time2 - time1) < waitTime);
}