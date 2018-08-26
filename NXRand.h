#pragma once

#include "Incl.h"

namespace nx
{
	template<typename T, typename = void>
	class Rand 
	{ 
		static_assert(std::is_arithmetic_v<T>, "Must be an arithmetic type (integral/floating).");
		Rand() {} 
	};
}

namespace nx
{
	template<typename T>
	class Rand<T, std::enable_if_t<std::is_integral_v<T>>>
	{
	public:
		Rand(T min, T max);
		Rand() {}

		void ResetRange();
		void SetRange(T min, T max);
		void ResetState();

		void Seed(T value);
		void Seed(std::seed_seq aSeedSequence);

		std::pair<T, T> GetRange() const;

		static T Next();
		static T Next(T max);
		static T Next(T min, T max);

		T operator()(T min, T max, bool retain = true);
		T operator()();

	private:
		void Check(T min, T max);

	private:
		std::uniform_int_distribution<T> mDist;
		std::default_random_engine mGen;
		std::random_device mRand;
	};
}

namespace nx
{
	template<typename T>
	class Rand<T, std::enable_if_t<std::is_floating_point_v<T>>>
	{
	public:
		Rand(T min, T max);
		Rand() {}

		void ResetRange();
		void SetRange(T min, T max);
		void ResetState();

		void Seed(T value);
		void Seed(std::seed_seq aSeedSequence);

		std::pair<T, T> GetRange() const;

		static T Next();
		static T Next(T max);
		static T Next(T min, T max);

		T operator()(T min, T max, bool retain = true);
		T operator()();

	private:
		void Check(T min, T max);

	private:
		std::uniform_real_distribution<T> mDist;
		std::default_random_engine mGen;
		std::random_device mRand;
	};
}

namespace nx
{
	using iRand = Rand<int>;
	using fRand = Rand<float>;
	using dRand = Rand<double>;
}

#include "RandInt.inl"
#include "RandFloat.inl"