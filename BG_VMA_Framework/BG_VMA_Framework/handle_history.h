/*
	author : Lin Du
	time : 2015-06-23
*/
#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Handle_history
{
public:
	vector<bool> success;
	vector<double> time_used;
	vector<int> problem_size;
	
	Handle_history()
	{
		success.clear();
		time_used.clear();
		problem_size.clear();
	}
	void save_history(bool r_success, double r_time_used, int r_problem_size)
	{
		success.push_back(r_success);
		time_used.push_back(r_time_used);
		problem_size.push_back(r_problem_size);
	}

	int get_first_rej()
	{
		for (int i = 0; i < success.size(); i ++)
		{
			if (!success[i])
				return i + 1;
		}
		return success.size() + 1;
	}

	void save_to_file(string filename)
	{
		ofstream fout(filename);
		for (int i = 0; i < success.size(); i ++)
		{
			fout << i << ", success:" << success[i] << ", time:" << time_used[i] << ", vm_num:" << problem_size[i] << endl;
		}
		fout.close();
	}
};