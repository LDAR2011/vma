/*
	author : Lin Du
	time : 2015-06-23
*/
#include "VM_Scheme.h"
#include "DCN.h"

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

	Oktopus_Handler(){}
	~Oktopus_Handler() {}

	Oktopus_Handler(int nodeCount);

	vector<int> available_slots;

	int calcSlots(int id, DCN& dcn, VC_Request vc_request);

	VM_Scheme handle_VC_Request(DCN& dcn, VC_Request vc_request);

	VM_Scheme handle_VOC_Request(DCN& dcn, VOC_Request voc_request);

};