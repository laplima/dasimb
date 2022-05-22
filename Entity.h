#ifndef ENTITY_H
#define ENTITY_H

#include "EntityBase.h"
#include "EntitySet.h"
// #include "Stateful.h"
#include "StatefulEntity.h"

enum class State { INITIATOR, IDLE, VISITED, OK };

class Entity : public StatefulEntity<State> {
public:
	explicit Entity(ID id);
	void spontaneously() override;
	void receiving(EntityBase* origin, const Message& m) override;
	void when() override;
protected:
	void visits();
	EntitySet unvisited;
	bool initiator = false;
	EntityBasePtr entry = nullptr;
};

#endif
