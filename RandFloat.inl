namespace nx
{
#define IS_FLOAT std::enable_if_t<std::is_floating_point_v<T>>

	template<typename T>
	Rand<T, IS_FLOAT>::Rand(T min, T max) : mDist(min, max), mGen(mRand())
	{
		Check(min, max);

	}

	template<typename T>
	void Rand<T, IS_FLOAT>::ResetRange()
	{
		auto myNew = mDist.param();
		myNew._Init(static_cast<T>(0), std::numeric_limits<T>::max());

		mDist.param(myNew);
	}

	template<typename T>
	void Rand<T, IS_FLOAT>::SetRange(T min, T max)
	{
		Check(min, max);

		auto myNew = mDist.param();
		myNew._Init(min, max);

		mDist.param(myNew);
	}

	template<typename T>
	void Rand<T, IS_FLOAT>::Seed(T value)
	{
		mGen.seed(value);
	}

	template<typename T>
	void Rand<T, IS_FLOAT>::Seed(std::seed_seq aSeedSequence)
	{
		mGen.seed(aSeedSequence);
	}

	template<typename T>
	void Rand<T, IS_FLOAT>::ResetState()
	{
		mDist.reset();
	}

	template<typename T>
	std::pair<T, T> Rand<T, IS_FLOAT>::GetRange() const
	{
		return std::make_pair(mDist.min(), mDist.max());
	}

	template<typename T>
	T Rand<T, IS_FLOAT>::operator()(T min, T max, bool retain)
	{
		Check(min, max);

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
	T Rand<T, IS_FLOAT>::operator()()
	{
		return mDist(mGen);
	}

	template<typename T>
	void Rand<T, IS_FLOAT>::Check(T min, T max)
	{
		if (min > max)
			mDist.param(std::uniform_real<T>(max, min).param());
	}

	template<typename T>
	T Rand<T, IS_FLOAT>::Next()
	{
		std::uniform_real_distribution<T> myDist;

		std::random_device myRand;
		static std::default_random_engine myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, IS_FLOAT>::Next(T max)
	{
		std::uniform_real_distribution<T> myDist(static_cast<T>(0), max);

		std::random_device myRand;
		static std::default_random_engine myGen(myRand());

		return myDist(myGen);
	}

	template<typename T>
	T Rand<T, IS_FLOAT>::Next(T min, T max)
	{
		std::uniform_real_distribution<T> myDist(min, max);

		if (min > max)
			myDist.param(std::uniform_real<T>(max, min).param());

		std::random_device myRand;
		static std::default_random_engine myGen(myRand());

		return myDist(myGen);
	}

#undef IS_FLOAT
}