/*
	author : Lin Du
	time: 2015-06-18
*/
#pragma once

#include <vector>
#include <algorithm>
#include <hash_set>
#include <hash_map>
#include <fstream>
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
	int slots;
	vector<int> arys;
	vector<int> link_capacitys;
	vector<int> level_start_index;

	bool isServer(int id) const;
	int get_level(int id) const;
	int get_parent_id(int id) const;
	int get_leftest_child_id(int id) const;
	int get_rightest_child_id(int id) const;
	int calcslots(int id);

	//
	int time;
	vector<VM_Scheme> vm_schemes;

	void add_vm_scheme(VM_Scheme vm_scheme, ofstream& fout, bool verbose=false);
	void remove_vm_scheme(ofstream& fout, bool verbose = false);

	void occupy_resource(VM_Scheme& vm_scheme);
	void release_resource(VM_Scheme& vm_scheme);

	void update_resource(VM_Scheme & vm_scheme, bool isOccupy);

	DCN() {};
	~DCN() {};

	DCN(int r_layers, vector<int>r_arys, vector<int>r_link_capacitys, int r_slots);


	void record_resource(ofstream& fout);
	void record_resource(ofstream& fout, vector<int>& available_slots);
};