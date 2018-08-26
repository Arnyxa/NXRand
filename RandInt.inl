namespace nx
{
#define IS_INT std::enable_if_t<std::is_integral_v<T>>

	template<typename T>
	Rand<T, IS_INT>::Rand(T aMin, T aMax) : mDist(aMin, aMax)
	{
		Check(aMin, aMax);
	}

	template<typename T>
	void Rand<T, IS_INT>::Reset()
	{
		auto myNew = mDist.param();
		myNew._Init(0, std::numeric_limits::max());

		mDist.param(myNew);
	}

	template<typename T>
	void Rand<T, IS_INT>::Reset(T aMin, T aMax)
	{
		Check(aMin, aMax);

		auto myNew = mDist.param();
		myNew._Init(aMin, aMax);

		mDist.param(myNew);
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
	T Rand<T, IS_INT>::operator()(T aMin, T aMax, bool retain)
	{
		Check(aMin, aMax);

		auto myOldState = mDist.param();
		auto myNewState = mDist.param();

		myNewState._Init(aMin, aMax);
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
	void Rand<T, IS_INT>::Check(T aMin, T aMax)
	{
		assert(aMin <= aMax && "Min value can not be greater than max value.");
	}

#undef IS_INT
}