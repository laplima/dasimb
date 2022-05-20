#ifndef ENTITY_H
#define ENTITY_H

#include "EntityBase.h"
#include "Stateful.h"

enum class State { INITIATOR, IDLE, OK };

class Entity : public EntityBase, public Stateful<State> {
public:
	Entity(ID id) : EntityBase{id}, Stateful{State::IDLE} {}
	void spontaneously() override;
	void receiving(EntityBase* origin, const Message& m) override;
	void when() override;
};

#endif
