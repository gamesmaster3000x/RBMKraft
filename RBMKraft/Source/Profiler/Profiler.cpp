#include "Profiler.h"

Profiler::Profiler() 
{
	startTime = glfwGetTime();
	lastLap = startTime;
}

double Profiler::GetTotal() 
{
	return glfwGetTime() - startTime;
}

double Profiler::GetLap()
{
	return glfwGetTime() - lastLap;
}

void Profiler::SetLap()
{
	lastLap = glfwGetTime();
}
