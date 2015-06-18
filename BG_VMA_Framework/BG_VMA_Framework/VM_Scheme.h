/*
	author : Lin Du
	time: 2015-06-18
*/
#pragma once

#include<map>
using namespace std;

class VM_Scheme
{
public:
	int vm_num;
	map<int, int>vm_map;
	int arrival_time;
	int compute_time;
	int expire_time;
	VM_Scheme(){}
	~VM_Scheme() {}
};