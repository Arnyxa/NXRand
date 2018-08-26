#pragma once

#include <random>
#include <cassert>
#include <limits>

namespace nx
{
	template<typename T, typename = void>
	class Rand 
	{ Rand() {} };

}

namespace nx
{
	template<typename T>
	class Rand<T, std::enable_if_t<std::is_integral_v<T>>>
	{
	public:
		Rand(T aMin, T aMax);
		Rand() {}

		void Reset();
		void Reset(T aMin, T aMax);
		void ResetState();

		std::pair<T, T> GetRange() const;

		T operator()(T aMin, T aMax, bool retain = true);
		T operator()();

	private:
		void Check(T aMin, T aMax);

	private:
		std::uniform_int_distribution<T> mDist;
		std::default_random_engine mGen;
	};
}

#include "RandInt.inl"

namespace nx
{
	template<typename T>
	class Rand<T, std::enable_if_t<std::is_floating_point_v<T>>>
	{
	public:
		Rand(T aMin, T aMax);
		Rand() {}

		void Reset();
		void Reset(T aMin, T aMax);
		void ResetState();

		std::pair<T, T> GetRange() const;

		T operator()(T aMin, T aMax, bool retain = true);
		T operator()();

	private:
		void Check(T aMin, T aMax);

	private:
		std::uniform_real_distribution<T> mDist;
		std::default_random_engine mGen;
	};
}

#include "RandFloat.inl"