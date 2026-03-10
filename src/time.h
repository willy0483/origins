#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

struct Time
{
	double lastTime = 0.0;
	double nowTime = 0.0;
	double deltaTime = 0.0;
};

#endif
