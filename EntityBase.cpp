#include "EntityBase.h"
#include "EntitySet.h"
#include "Simulator.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

void EntityBase::add_neighbor(EntityBase* e)
{
	if (e != this && not is_neighbor(e)) {
		neighbors_ << e;
		e->add_neighbor(this);
	}
}

bool EntityBase::is_neighbor(EntityBase* e) const
{
	return neighbors_.contains(e);
}

EntityBase* EntityBase::neighbor(ID id) const
{
	auto n = std::find_if(std::begin(neighbors_),
		std::end(neighbors_),
		[id](const EntityBase* eb) { return eb->id() == id; });
	return (n == neighbors_.end()) ? nullptr : *n;
}

Message EntityBase::next_msg()
{
	if (inqueue_.empty())
		throw std::underflow_error{"no next message"};
	auto m = inqueue_.front();
	inqueue_.pop();
	return m;
}

void EntityBase::ispontaneously(Simulator* sim)
{
	if (simulator == nullptr)
		simulator = sim;
	spontaneously();
}

void EntityBase::ireceiving(Simulator* sim, EntityBase* origin)
{
	if (simulator == nullptr)
		simulator = sim;
	receiving(origin,next_msg());
}

void EntityBase::iwhen(Simulator* sim)
{
}

void EntityBase::send(const Message& m, const EntitySet& to)
{
	for (auto* e : to) {
		e->insert_message(m);
		simulator->schedule({EventType::receiving,this,e});
	}
}

void EntityBase::set_alarm(unsigned long)
{
	// to do
}
