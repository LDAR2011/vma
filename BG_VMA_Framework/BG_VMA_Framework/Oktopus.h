/*
	author : Lin Du
	time : 2015-06-23
*/
#include "VM_Scheme.h"
#include "DCN.h"
#include "handle_history.h"

class VC_Request
{
public:
	int N;
	int B;
	VC_Request(){};
	~VC_Request(){};

	VC_Request(int r_N, int r_B)
	{
		N = r_N;
		B = r_B;
	}
};

class VOC_Request
{
	int N;
	int B;
	int S;
	int O;

	VOC_Request(){};
	~VOC_Request() {};

	VOC_Request(int r_N, int r_B, int r_S, int r_O)
	{
		N = r_N;
		B = r_B;
		S = r_S;
		O = r_O;
	}
};

class Oktopus_Handler
{

public :

	Handle_history handle_history;

	Oktopus_Handler()
	{
		handle_history = Handle_history();
	}

	~Oktopus_Handler() {}

	Oktopus_Handler(int nodeCount);

	vector<int> available_slots;

	int calc_mv(int kv, int N, int B, int link_capacity);

	int calcSlots(int id, const DCN& dcn, VC_Request& vc_request);

	VM_Scheme handle_VC_Request(const DCN& dcn, VC_Request& vc_request);

	VM_Scheme handle_VOC_Request(const DCN& dcn, VOC_Request& voc_request);

	int hoseAlloc(const DCN& dcn, int node_id, VC_Request& vc_request, int m, VM_Scheme& vm_scheme);

};