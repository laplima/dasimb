#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <queue>
#include "EntitySet.h"
#include "Topology.h"

enum class EventType { spontaneously, receiving, when };

struct Event {
	EventType type;
	EntityBase* origin;
	EntityBase* target;
};

class Simulator {
public:
	explicit Simulator(Topology& t);
	void start(ID initiator);
	void schedule(const Event& ev);
private:
	Topology& topology;
	std::queue<Event> equeue;
};

#endif
