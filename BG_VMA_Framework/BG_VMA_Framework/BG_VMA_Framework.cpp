// BG_VMA_Framework.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.h"


int _tmain(int argc, _TCHAR* argv[])
{
	vector<int>arys;
	
	arys.push_back(20);
	arys.push_back(20);
	arys.push_back(40);


	vector<int>link_capacitys;
	link_capacitys.push_back(0);
	link_capacitys.push_back(32000);
	link_capacitys.push_back(8000);
	link_capacitys.push_back(1000);

	DCN test_dcn = DCN(3, arys, link_capacitys, 16);

	test_node_relation(test_dcn);

	cin.get();
	return 0;
}


