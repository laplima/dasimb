#ifndef ENTITY_H
#define ENTITY_H

#include "SEntityBase.h"

enum class State { INITIATOR, IDLE, OK };

class Entity : public SEntityBase<State> {
public:
	Entity(ID id) : SEntityBase<State>{id,State::IDLE} {}
	void spontaneously() override;
	void receiving(EntityBase* origin, const Message& m) override;
	void when() override;
};

#endif
