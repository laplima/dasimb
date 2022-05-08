#ifndef ENTITYBASE_H
#define ENTITYBASE_H

#include <string>
#include <queue>
#include <set>
#include "EntitySet.h"

class Simulator;

using ID = unsigned short;
using Message = std::string;

class EntityBase {
public:
	explicit EntityBase(ID id) : id_{id} {}
	[[nodiscard]] ID id() const { return id_; }
	void add_neighbor(EntityBase* e);
	[[nodiscard]] bool is_neighbor(EntityBase* e) const;
	[[nodiscard]] EntityBase* neighbor(ID id) const;
	[[nodiscard]] const EntitySet& N() const { return neighbors_; }
public:
	// user defined events
	virtual void spontaneously() = 0;
	virtual void receiving(EntityBase* origin, const Message& m) = 0;
	virtual void when() = 0;
public:
	// internal events (called by the simulator)
	void ispontaneously(Simulator* sim);
	void ireceiving(Simulator* sim, EntityBase* origin);
	void iwhen(Simulator* sim);
public:
	void insert_message(Message m) { inqueue_.emplace(m); }
	Message next_msg();
protected:
	void send(const Message& m, const EntitySet& to);
	void set_alarm(unsigned long t);
protected:
	ID id_;
	EntitySet neighbors_;
	std::queue<Message> inqueue_;
	Simulator* simulator = nullptr;
};

#endif
