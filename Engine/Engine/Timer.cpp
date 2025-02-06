#include "PreCompiledHeader.h"
#include "Timer.h"

Timer::Timer(float setTime)
	: setTime(setTime)
{
}

void Timer::Update(float delayTime)
{
	elapsedTime += delayTime;
}

void Timer::Reset()
{
	elapsedTime = 0.0f;
}