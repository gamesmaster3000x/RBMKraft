#ifndef PROFILER
#define PROFILER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Profiler
{
private:
	double startTime;

	double lastLap;

public:
	Profiler();

	double GetTotal();
	
	double GetLap();

	void SetLap();
};

#endif
