#pragma once

#include "SysCheck.h"
#include <random>
#include <chrono>
#include <limits>

namespace nx
{
	#if defined NX64
		using Mersenne = std::mt19937_64;
	#else
		using Mersenne = std::mt19937;
	#endif
}