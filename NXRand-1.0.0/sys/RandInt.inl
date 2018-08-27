namespace nx
{
#define IS_INT std::enable_if_t<std::is_integral_v<T>>

	template<typename T>
	Rand<T, IS_INT>::Rand(T min, T max) : mGen(mRand())
	{
		CheckValidity(min, max);
	}

	template<typename T>
	void Rand<T, IS_INT>::ResetRange()
	{
		mDist.param(std::uniform_int<T>(static_cast<T>(0), std::numeric_limits<T>::max()).param());
	}

	template<typename T>
	void Rand<T, IS_INT>::SetRange(T min, T max)
	{
		CheckValidity(min, max);
	}

	template<typename T>
	void Rand<T, IS_INT>::Seed(unsigned value)
	{
		mGen.seed(value);
	}

	template<typename T>
	void Rand<T, IS_INT>::Seed(std::seed_seq aSeedSequence)
	{
		mGen.seed(aSeedSequence);
	}

	template<typename T>
	void Rand<T, IS_INT>::ResetState()
	{
		mDist.reset();
	}

	template<typename T>
	std::pair<T, T> Rand<T, IS_INT>::GetRange() const
	{
		return std::make_pair(mDist.min(), mDist.max());
	}

	template<typename T>
	T Rand<T, IS_INT>::operator()(T min, T max, bool retain)
	{
		CheckValidity(min, max);

		auto myOldState = mDist.param();
		auto myNewState = mDist.param();

		myNewState._Init(min, max);
		mDist.param(myNewState);

		T myReturn = mDist(mGen);

		if (retain)
			mDist.param(myOldState);

		return myReturn;
	}

	template<typename T>
	T Rand<T, IS_INT>::operator()()
	{
		return mDist(mGen);
	}

	template<typename T>
	void Rand<T, IS_INT>::CheckValidity(T min, T max)
	{
		if (min > max)
		{
			T temp = min;
			min = max;
			max = temp;
		}

		mDist.param(std::uniform_int<T>(min, max).param());
	}

	template<typename T>
	T Rand<T, IS_INT>::Next()
	{
		std::uniform_int_distribution<T> myDist;

		std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, IS_INT>::Next(T max)
	{
		std::uniform_int_distribution<T> myDist(static_cast<T>(0), max);

		std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, IS_INT>::Next(T min, T max)
	{
		std::uniform_int_distribution<T> myDist(min, max);

		if (min > max)
			myDist.param(std::uniform_int<T>(max, min).param());

		std::random_device myRand;
		static Mersenne myGen(myRand());

		return myDist(myGen);
	}

#undef IS_INT
}