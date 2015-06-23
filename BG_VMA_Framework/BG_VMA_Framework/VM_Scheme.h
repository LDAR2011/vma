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
	
	//vm id --> node id
	map<int, int>vm_map;

	//node id --> uplink demand
	map<int, int>uplink_map;
	
	//node id --> downlink demand 
	map<int, int>downlink_map;


	int arrival_time;
	int during_time;
	int expire_time;

	VM_Scheme(){}
	~VM_Scheme() {}

	VM_Scheme(map<int, int>r_vm_map, int r_arrival_time, int r_during_time)
	{
		vm_map = r_vm_map;
		arrival_time = r_arrival_time;
		during_time = r_during_time;
		expire_time = arrival_time + during_time;
	}

	bool operator < (const VM_Scheme& vm_s)
	{
		return this->expire_time < vm_s.expire_time;
	}

	bool operator > (const VM_Scheme& vm_s)
	{
		return this->expire_time > vm_s.expire_time;
	}

	bool operator == (const VM_Scheme& vm_s)
	{
		return this->expire_time == vm_s.expire_time;
	}
};