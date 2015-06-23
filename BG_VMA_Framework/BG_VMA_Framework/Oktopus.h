/*
	author : Lin Du
	time : 2015-06-23
*/
#include "Request.h"

class VC_Request : public Request
{
	int B;
	VC_Request(){};
	~VC_Request(){};

	VC_Request(int r_N, int r_B)
	{
		N = r_N;
		B = r_B;
	}
};

class VOC_Request : public Request
{
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