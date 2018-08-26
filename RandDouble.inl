// double
namespace nx
{
	Rand<double>::Rand(double aMin, double aMax) : mDist(aMin, aMax)
	{
		Check(aMin, aMax);
	}

	void Rand<double>::Reset()
	{
		auto myNew = mDist.param();
		myNew._Init(0, std::numeric_limits<double>::max());

		mDist.param(myNew);
	}

	void Rand<double>::Reset(double aMin, double aMax)
	{
		Check(aMin, aMax);

		auto myNew = mDist.param();
		myNew._Init(aMin, aMax);

		mDist.param(myNew);
	}

	void Rand<double>::ResetState()
	{
		mDist.reset();
	}

	std::pair<double, double> Rand<double>::GetRange() const
	{
		return std::make_pair(mDist.min(), mDist.max());
	}

	double Rand<double>::operator()(double aMin, double aMax, bool retain = true)
	{
		Check(aMin, aMax);

		auto myOldState = mDist.param();
		auto myNewState = mDist.param();

		myNewState._Init(aMin, aMax);
		mDist.param(myNewState);

		double myReturn = mDist(mGen);

		if (retain)
			mDist.param(myOldState);

		return myReturn;
	}

	double Rand<double>::operator()()
	{
		return mDist(mGen);
	}

	void Rand<double>::Check(double aMin, double aMax)
	{
		assert(aMin <= aMax && "Min value can not be greater than max value.");
	}
}
