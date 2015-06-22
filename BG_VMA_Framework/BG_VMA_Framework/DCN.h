/*
	author : Lin Du
	time: 2015-06-18
*/
#pragma once

#include <vector>
using namespace std;

#include "VM_Scheme.h"

class Node
{
public:
	int id;
	int slots;
	
	int uplink_capacity;
	int downlink_capacity;
	
	Node() {};
	Node(int id, int slots, int link_capacity)
	{
		this->id = id;
		this->slots = slots;
		this->uplink_capacity = link_capacity;
		this->downlink_capacity = link_capacity;
	}
	
	bool operator < (const Node& n)const{
		return downlink_capacity + uplink_capacity < n.downlink_capacity + n.uplink_capacity;
	}
	~Node() {}
};

class DCN
{
public:
	int nodeCount;
	vector<Node> nodes;

	//topo definition
	int layers;
	vector<int> arys;
	vector<int> link_capacitys;
	vector<int> level_start_index;

	bool isServer(int id);
	int get_level(int id);
	int get_parent_id(int id);
	int get_leftest_child_id(int id);
	int get_rightest_child_id(int id);

	//
	int time;
	vector<VM_Scheme> schemes;
	

	DCN() {};
	~DCN() {};

	DCN(int r_layers, vector<int>r_arys, vector<int>r_link_capacitys, int r_slots);
};
