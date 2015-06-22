#include "stdafx.h"

void test_node_relation(DCN& dcn, int id)
{
	cout << "id:" << id << endl;
	cout << "level:" << dcn.get_level(id) << endl;
	cout << "parent:" << dcn.get_parent_id(id) << endl;
	cout << "left child:" << dcn.get_leftest_child_id(id) << endl;
	cout << "right child:" << dcn.get_rightest_child_id(id) << endl;
}

void test_node_relation(DCN& dcn, vector<int> ids)
{
	for (int i = 0; i < ids.size(); i++)
		test_node_relation(dcn, ids[i]);
}

void test_node_relation(DCN& dcn)
{
	vector<int> nodes;
	for (int i = 0; i < dcn.level_start_index.size()-1; i ++)
	{
		nodes.push_back(dcn.level_start_index[i]);
		nodes.push_back((dcn.level_start_index[i] + dcn.level_start_index[i+1]) / 2);
		nodes.push_back(dcn.level_start_index[i + 1] - 1);
	}
	test_node_relation(dcn, nodes);
}

