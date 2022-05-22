//
// Stateful Entity Base
// adds custom state (+ operation) to EntityBase
//

#ifndef STATEFULENTITY_H
#define STATEFULENTITY_H

#include "EntityBase.h"

template<typename State>
class StatefulEntity : public EntityBase {
public:
	StatefulEntity(ID id, State s) : EntityBase{id}, state_{s} {}
	State state() const { return state_; }
protected:
	void become(State new_state) { state_ = new_state; }
protected:
	State state_;
};

#endif
