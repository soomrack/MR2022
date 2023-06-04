
#include <iostream> 
#include <list>


class FSM_Exception : public std::exception
{
public:
	FSM_Exception(const char* const& msg) : exception(msg)
	{}
};

FSM_Exception DOES_NOT_EXISTS("Node with this key already exists\n");


void state0() {
	std::cout << "state 0" << std::endl;
}

void state1() {
	std::cout << "state 1" << std::endl;
}

void state2() {
	std::cout << "state 2" << std::endl;
}

void action(unsigned int num) {
	std::cout << "action number " << num << std::endl;
}

unsigned int KEY_FSM = 0;

class StateFSM {
protected:
	unsigned int key;
	void (*func)();
	std::list<StateFSM*> edges;


public:
	StateFSM(void (*func)());
	~StateFSM();

	void run();

	friend class FSM;
};

class FSM {
protected:
	unsigned int size = 0;
	std::list<StateFSM*> states;
	StateFSM* active_state = NULL;
	void set_state(StateFSM* state);

public:
	void active();


	FSM() = default;

	~FSM();

	void add_state(void (*new_func)());
	void add_edge(StateFSM* from, StateFSM* to, bool two_sides = 1);
	void add_edge(unsigned int key_from, unsigned int key_to, bool two_sides = 1);
	void del_state(unsigned int key);
	void del_edge(unsigned int key_from, unsigned int key_to, bool two_sides = 1);


	StateFSM* find_by_key(unsigned int key);

	void run();
};


StateFSM::StateFSM(void(*func)()) {
	this->key = KEY_FSM;
	this->func = func;

	++KEY_FSM;
}

StateFSM::~StateFSM() {
	std::list<StateFSM*>::iterator idx;
	for (StateFSM* temp : edges) {
		idx = (temp->edges).begin();
		for (StateFSM* check : temp->edges) {
			if (check->key == key) {
				temp->edges.erase(idx);
				break;
			}
			++idx;
		}
	}
	edges.clear();
	key = NULL;

}

void StateFSM::run() {
	func();
}

FSM::~FSM() {
	size = 0;
	states.clear();
}

void FSM::set_state(StateFSM* state) {
	this->active_state = state;
}

void FSM::active() {
	(*active_state).func();
}

void FSM::add_state(void (*new_func)()) {
	StateFSM* new_state = new StateFSM(new_func);
	states.push_back(new_state);
}

void FSM::add_edge(StateFSM* from, StateFSM* to, bool two_sides) {
	from->edges.push_back(to);
	if (two_sides) to->edges.push_back(from);
}

void FSM::add_edge(unsigned int key_from, unsigned int key_to, bool two_sides) {
	StateFSM* from = find_by_key(key_from);
	StateFSM* to = find_by_key(key_to);
	add_edge(from, to, two_sides);
}

StateFSM* FSM::find_by_key(unsigned int key) {
	for (StateFSM* temp : states) {
		if (temp->key == key) return temp;
	}
	throw DOES_NOT_EXISTS;
}

void FSM::del_state(unsigned int key) {
	StateFSM* del_state = find_by_key(key);
	std::list<StateFSM*>::iterator state_idx, edge_idx, idx_to_del;
	state_idx = states.begin();;
	for (StateFSM* temp : states) {
		if (temp == del_state) {
			idx_to_del = state_idx;
		}
		edge_idx = (temp->edges).begin();
		for (StateFSM* check : temp->edges) {
			if (check->key == key) {
				temp->edges.erase(edge_idx);
				break;
			}
			++edge_idx;
		}
		++state_idx;
	}
	states.erase(idx_to_del);
}

void FSM::del_edge(unsigned int key_from, unsigned int key_to, bool two_sides) {
	StateFSM* from = find_by_key(key_from);
	StateFSM* to = find_by_key(key_to);
	std::list<StateFSM*>::iterator idx;
	bool from_done = 0;
	bool to_done;
	two_sides ? to_done = 0 : 1;
	for (StateFSM* temp : states) {
		idx = temp->edges.begin();
		if (temp == from) {
			for (StateFSM* check : temp->edges) {
				if (check == to) {
					temp->edges.erase(idx);
					break;
				}
			}
		}
		if (two_sides and temp == to) {
			for (StateFSM* check : temp->edges) {
				if (check == to) {
					temp->edges.erase(idx);
					break;
				}
			}
		}
		if (from_done and to_done) break;
	}
}

void FSM::run() {
	set_state(states.front());
	int choice;
	while (true) {
		std::cout << "Press -1 to stop" << std::endl;
		std::cout << "Or choose action:" << std::endl;
		std::list<StateFSM*>::iterator idx;
		for (StateFSM* temp : (*active_state).edges) {
			std::cout << (*temp).key << " ";
		}
		std::cout << std::endl;
		std::cin >> choice;
		action(choice);
		if (choice == -1) {
			break;
		}
		set_state(find_by_key(choice));
		active();
	}
}


int main() {
	FSM A;
	A.add_state(&state0);
	A.add_state(&state1);
	A.add_state(&state2);

	A.add_edge(0, 1);
	A.add_edge(0, 2, 0);
	A.add_edge(1, 2);

	try {
		A.run();
	}
	catch (const FSM_Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}