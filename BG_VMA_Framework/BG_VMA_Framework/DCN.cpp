#include "stdafx.h"
#include "DCN.h"
#include <assert.h>
using namespace std;

DCN::DCN(int r_layers, vector<int>r_arys, vector<int>r_link_capacitys, int r_slots)
{

	//topo set up

	layers = r_layers;

	assert(layers == r_arys.size());
	assert(layers + 1 == r_link_capacitys.size());

	arys = r_arys;
	link_capacitys = r_link_capacitys;

	level_start_index.resize(layers + 2);
	
	nodeCount = 1;
	level_start_index[0] = 0;
	level_start_index[1] = 1;
	for (int i = 1; i < layers+1; i ++){
		int level_cnt = 1;
		for (int j = 0; j < i; j++){
			level_cnt *= arys[j];
		}
		nodeCount += level_cnt;
		level_start_index[i + 1] = level_start_index[i] + level_cnt;
	}
	
	/*
	cout << "node cnt:" << nodeCount << endl;
	for (int i = 0; i < level_start_index.size(); i++)
		cout << "level start:" <<level_start_index[i] << endl;
	*/

	for (int i = 0; i < layers + 1; i ++){
		for (int j = level_start_index[i]; j < level_start_index[i + 1]; j++){
			Node newNode;
			if (isServer(j)){
				newNode = Node(j, r_slots, r_link_capacitys[i]);
			}
			else{
				newNode = Node(j, 0, r_link_capacitys[i]);
			}
			nodes.push_back(newNode);
		}
	}
	
	//cout << "node size:" << nodes.size() << endl;

	//set time
	time = 0;

	//vm scheme clear up
	vm_schemes.clear();
}


bool DCN::isServer(int id) const
{
	if (id >= level_start_index[level_start_index.size() - 2])
		return true;
	return false;
}

int DCN::get_level(int id) const
{
	assert(id >= 0 && id < nodeCount);

	int level = 0;
	while (id >= level_start_index[level])
	{
		level++;
	}

	assert(id < level_start_index[level]);

	level -= 1;

	return level;
}

int DCN::get_parent_id(int id) const
{
	int level = get_level(id);

	if (level <= 0) // root node
		return -1;

	return level_start_index[level - 1] + (id - level_start_index[level]) / arys[level - 1];
}

int DCN::get_leftest_child_id(int id) const
{
	int level = get_level(id);

	if (level >= layers)// server node
		return -1;

	return level_start_index[level + 1] + (id - level_start_index[level]) * arys[level];

}

int DCN::get_rightest_child_id(int id) const
{
	int level = get_level(id);

	if (level >= layers)// server node
		return -1;

	return get_leftest_child_id(id) + arys[level] - 1;
}

void DCN::add_vm_scheme(VM_Scheme vm_scheme)
{
	vm_schemes.push_back(vm_scheme);

	//# alternative #
	//occupy resource
	occupy_resource(vm_scheme);
}

void DCN::remove_vm_scheme()
{
	sort(vm_schemes.begin(), vm_schemes.end());
	reverse(vm_schemes.begin(), vm_schemes.end());
	//DESC order

	time++;

	while (vm_schemes.end()->expire_time >= time)
	{
		//TODO
		//release resource
		release_resource(*vm_schemes.end());
		vm_schemes.pop_back();
		
	}
}

void DCN::occupy_resource(VM_Scheme& vm_scheme)
{
	update_resource(vm_scheme, true);
}

void DCN::release_resource(VM_Scheme& vm_scheme)
{
	update_resource(vm_scheme, false);
}

void DCN::update_resource(VM_Scheme & vm_scheme, bool isOccupy)
{
	//slot update
	map<int, int>::iterator it;
	for (it = vm_scheme.node_slot_map.begin(); it != vm_scheme.node_slot_map.end(); it ++)
	{
		if (isOccupy) // occupy resource
			nodes[it->first].slots -= it->second;
		else
			nodes[it->first].slots += it->second;
	}

	//uplink update
	for (it = vm_scheme.uplink_map.begin(); it != vm_scheme.uplink_map.end(); it++)
	{
		if (isOccupy) //occupy
			nodes[it->first].uplink_capacity -= it->second;
		else //release
			nodes[it->first].uplink_capacity += it->second;
	}

	//downlink update
	for (it = vm_scheme.downlink_map.begin(); it != vm_scheme.downlink_map.end(); it++)
	{
		if (isOccupy)
			nodes[it->first].downlink_capacity -= it->second;
		else
			nodes[it->first].downlink_capacity += it->second;
	}
}