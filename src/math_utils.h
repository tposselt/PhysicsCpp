#pragma once
#include <cstdlib>
#include <algorithm>

inline float randomf()
{
	// return a random float 0 - 1
	return rand() / (float)RAND_MAX;
}

inline float randomf(float max)
{
	return randomf() * max;
}

inline float randomf(float min, float max)
{
	if (min > max) std::swap(min, max);
	return min + (randomf() * (max - min));
}
