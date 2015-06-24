// BG_VMA_Framework.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.h"
#include "simulation.h"


int _tmain(int argc, _TCHAR* argv[])
{
	vector<int>arys;
	
	arys.push_back(10);
	arys.push_back(10);
	arys.push_back(10);


	vector<int>link_capacitys;
	link_capacitys.push_back(0);
	link_capacitys.push_back(4000);
	link_capacitys.push_back(2000);
	link_capacitys.push_back(1000);

	DCN dcn = DCN(3, arys, link_capacitys, 4);

	NumGen* vmGen = new UniformNumGen(8,32);
	NumGen* bwGen = new UniformNumGen(100, 900);
	NumGen*  timeGen = new UniformNumGen(10, 40);

	test_Oktopus_VC(dcn,vmGen,bwGen,2000,timeGen);

	cin.get();
	return 0;
}


