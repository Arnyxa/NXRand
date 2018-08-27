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

namespace nx
{
	template<typename T>
	using is_float = std::enable_if_t<std::is_floating_point<T>::value>;
	template<typename T>
	using is_int = std::enable_if_t<std::is_integral<T>::value>;
	template<typename T>
	using is_arithmetic = typename std::is_arithmetic<T>::value;
}