#include "stdafx.h"
#include "Oktopus.h"

Oktopus_Handler::Oktopus_Handler(int nodeCount)
{
	available_slots.clear();

	for (int i = 0; i < nodeCount; i ++)
	{
		available_slots.push_back(0);
	}
}

int Oktopus_Handler::calc_mv(int kv, int N, int B, int link_capacity)
{
	int upper_bound = min(kv, N);

	for (int m = upper_bound; m >= 0; m --)
	{
		if (min(m, N-m) * B <= link_capacity)
		{
			return m;
		}
	}

	return 0;
}

int Oktopus_Handler::calcSlots(int id, const DCN& dcn, VC_Request& vc_request)
{
	if (dcn.isServer(id))
	{
		available_slots[id] = calc_mv(dcn.nodes[id].slots, vc_request.N, vc_request.B, dcn.nodes[id].uplink_capacity);
		
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
		available_slots[id] = calc_mv(available_slots[id], vc_request.N, vc_request.B, dcn.nodes[id].uplink_capacity);
	}

	return available_slots[id];
}

VM_Scheme Oktopus_Handler::handle_VC_Request(const DCN& dcn, VC_Request& vc_request)
{
	VM_Scheme vm_scheme = VM_Scheme();

	calcSlots(0, dcn, vc_request);

	vm_scheme.isSuccess = false;

	for (int i = dcn.nodeCount - 1; i >= 0; i --)
	{
		if (available_slots[i] >= vc_request.N)
		{
			hoseAlloc(dcn, i, vc_request, vc_request.N, vm_scheme);
			vm_scheme.isSuccess = true;
			break;
		}
	}

	return vm_scheme;
}

VM_Scheme Oktopus_Handler::handle_VOC_Request(const DCN& dcn, VOC_Request& voc_request)
{
	VM_Scheme vm_scheme = VM_Scheme();

	//TODO

	return vm_scheme;
}

int Oktopus_Handler::hoseAlloc(const DCN& dcn, int node_id, VC_Request& vc_request, int m, VM_Scheme& vm_scheme)
{
	if (dcn.isServer(node_id))
	{
		//record slot
		vm_scheme.node_slot_map[node_id] = m;
		
		int bw_reserve = min(m, vc_request.N - m) * vc_request.B;
		//record uplink
		vm_scheme.downlink_map[node_id] = bw_reserve;

		//record downlink
		vm_scheme.uplink_map[node_id] = bw_reserve;

		return m;
	}

	int leftchild_id = dcn.get_leftest_child_id(node_id);
	int rightchild_id = dcn.get_rightest_child_id(node_id);
	int vm_allocated = 0;
	for (int i = leftchild_id; i <= rightchild_id; i ++)
	{
		if (vm_allocated < m)
		{	
			int node_capacity = min(m - vm_allocated, available_slots[i]);
			int node_alloc = hoseAlloc(dcn, i, vc_request, node_capacity, vm_scheme);
			vm_allocated += node_alloc;
			if (!dcn.isServer(i))
			{
				int bw_reserve = min(node_alloc, vc_request.N - node_alloc) * vc_request.B;

				//record uplink
				vm_scheme.uplink_map[i] = bw_reserve;

				//record downlink
				vm_scheme.downlink_map[i] = bw_reserve;
			}
		}
	}
	return vm_allocated;
}