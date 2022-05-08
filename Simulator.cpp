#include "Simulator.h"

Simulator::Simulator(Topology& t)
	: topology{t}
{
}

void Simulator::schedule(const Event& ev)
{
	equeue.push(ev);
}

void Simulator::start(ID initiator)
{
	schedule({EventType::spontaneously,nullptr,topology[initiator]});

	while (not equeue.empty()) {
		auto ev = equeue.front();
		equeue.pop();
		switch (ev.type) {
			using enum EventType;
			case spontaneously:
				ev.target->ispontaneously(this);
				break;
			case receiving:
				ev.target->ireceiving(this,ev.origin);
				break;
			case when:
				ev.target->iwhen(this);
				break;
		}
	}
}
