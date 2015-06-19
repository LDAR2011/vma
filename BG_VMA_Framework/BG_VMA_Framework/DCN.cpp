#include "DCN.h"
#include <assert.h>

DCN::DCN(int layers, vector<int>r_arys, vector<int>r_link_capacitys)
{
	assert(layers == r_arys.size());
	assert(layers == r_link_capacitys.size());

	arys = r_arys;
	link_capacitys = r_link_capacitys;

	level_start_index.resize(layers);
	
	nodeCount = 1;
	level_start_index[0] = 1;
	for (int i = 0; i < layers; i ++){
		int level_cnt = 1;
		for (int j = 0; j <= i; j++){
			level_cnt *= arys[j];
		}
		nodeCount += level_cnt;
		if (i != layers - 1){
			level_start_index[i + 1] = level_start_index[i] + level_cnt;
		}
	}


}