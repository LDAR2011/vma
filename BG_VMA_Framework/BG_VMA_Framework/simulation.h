/*
	author : Lin Du
	time : 2015-06-23
*/
#pragma once

#include "stdafx.h"
#include "Oktopus.h"
#include "time.h"

#include <random>

class NumGen
{
public: 
	virtual int get_num() = 0;
};

class UniformNumGen : public NumGen
{
	int begin;
	int end;
	
	default_random_engine generator;
	uniform_int_distribution<int> dis;

public: 

	~UniformNumGen(){}

	UniformNumGen(int r_begin, int r_end)
	{
		begin = r_begin;
		end = r_end;
		dis = uniform_int_distribution<int>(begin, end);
	}

	virtual int get_num()
	{
		return dis(generator);
	}
};

class PoissonGen : public NumGen
{
	int mean;

	default_random_engine generator;
	poisson_distribution<int> dis;

public:

	~PoissonGen(){}

	PoissonGen(int r_mean)
	{
		mean = r_mean;
		dis = poisson_distribution<int>(mean);
	}

	virtual int get_num()
	{
		return dis(generator);
	}
};

DCN copy_dcn(const DCN& dcn)
{
	DCN new_DCN = DCN(dcn.layers, dcn.arys, dcn.link_capacitys, dcn.slots);
	return new_DCN;
}


void test_Oktopus_VC(DCN& dcn, NumGen* vmNumGen, NumGen* bwGen, int looptime, NumGen* timeGen)
{

	Oktopus_Handler oktopus_handler = Oktopus_Handler();

	clock_t start, end;

	for (int i = 0; i < looptime; i ++)
	{
		int n = vmNumGen->get_num();
		int b = bwGen->get_num();

		VC_Request vc_request = VC_Request(n, b);

		start = clock();
		
		VM_Scheme vm_scheme = oktopus_handler.handle_VC_Request(dcn, vc_request);
		
		end = clock();
		
		double dur = (double)(end - start) / (double)CLOCKS_PER_SEC;

		vm_scheme.set_time(i, timeGen->get_num());

		if (vm_scheme.isSuccess)
		{
			dcn.add_vm_scheme(vm_scheme);
		}

		dcn.remove_vm_scheme();
	}
}