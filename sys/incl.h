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
	auto is_arithmetic = std::is_arithmetic<T>::value;
	template<typename T>
	auto is_bool = std::is_same<T, bool>::value;

	template<typename T>
	using if_float = std::enable_if_t<std::is_floating_point<T>::value>;
	template<typename T>
	using if_int = std::enable_if_t<std::is_integral<T>::value>;
	template<typename T>
	using if_bool = std::enable_if_t<is_bool<T>>;

	using param_bool = typename std::bernoulli_distribution::param_type;
	template<typename T>
	using param_int = typename std::uniform_int_distribution<T>::param_type;
	template<typename T>
	using param_real = typename std::uniform_real_distribution<T>::param_type;
}