/*
	author : Lin Du
	time : 2015-06-23
*/

#include "stdafx.h"
#include "Oktopus.h"

#include <random>

class DuringTimeGen
{
public: 
	virtual int get_during_time() = 0;
};

class UniformTimeGen: public DuringTimeGen
{
	int begin;
	int end;
	
	default_random_engine generator;
	uniform_int_distribution<int> dis;

public: 

	~UniformTimeGen(){}

	UniformTimeGen(int r_begin, int r_end)
	{
		begin = r_begin;
		end = r_end;
		dis = uniform_int_distribution<int>(begin, end);
	}

	int get_during_time()
	{
		return dis(generator);
	}
};

class PoissonTimeGen : public DuringTimeGen
{
	int mean;

	default_random_engine generator;
	poisson_distribution<int> dis;

public:

	~PoissonTimeGen(){}

	PoissonTimeGen(int r_mean)
	{
		mean = r_mean;
		dis = poisson_distribution<int>(mean);
	}

	int get_during_time()
	{
		return dis(generator);
	}
};
