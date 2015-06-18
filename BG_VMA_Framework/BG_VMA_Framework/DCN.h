class Node
{
public:
	int id;
	int slots;
	
	int uplink_capacity;
	int downlink_capacity;
	
	Node() {};
	Node(int slots, int link_capacity)
	{
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

};
