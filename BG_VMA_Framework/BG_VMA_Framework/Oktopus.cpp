#include "Oktopus.h"

Oktopus_Handler::Oktopus_Handler(int nodeCount)
{
	available_slots.clear();

	available_slots.resize(nodeCount);
}

int Oktopus_Handler::calcSlots(int id, DCN& dcn, VC_Request vc_request)
{
	if (dcn.isServer(id))
	{
		available_slots[id] = dcn.nodes[id].slots;
		
		if (available_slots[id] > dcn.nodes[id].uplink_capacity / vc_request.B)
			available_slots[id] = dcn.nodes[id].uplink_capacity / vc_request.B;
		
		return available_slots[id];
	}

	int leftChild_id = dcn.get_leftest_child_id(id);
	int rightChild_id = dcn.get_rightest_child_id(id);

	available_slots[id] = 0;
	for (int i = leftChild_id; i <= rightChild_id; i ++)
	{
		available_slots[id] += calcSlots(i, dcn, vc_request);
	}
	if (id != 0)
	{
		if (available_slots[id] > dcn.nodes[id].uplink_capacity / vc_request.B)
			available_slots[id] = dcn.nodes[id].uplink_capacity / vc_request.B;
	}

	return available_slots[id];
}

VM_Scheme Oktopus_Handler::handle_VC_Request(DCN& dcn, VC_Request vc_request)
{
	VM_Scheme vm_scheme = VM_Scheme();



	return vm_scheme;
}

VM_Scheme Oktopus_Handler::handle_VOC_Request(DCN& dcn, VOC_Request voc_request)
{
	VM_Scheme vm_scheme = VM_Scheme();

	//TODO

	return vm_scheme;
}