#pragma once

#include "SysCheck.h"
#include <random>
#include <chrono>
#include <limits>

namespace nx
{
	#if defined NX64
		using Mersenne = std::mt19937_64;
	#elif defined NX32 || defined NXUNKNOWN
		using Mersenne = std::mt19937;
	#endif
}