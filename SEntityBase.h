//
// Stateful Entity Base
// adds custom state (+ operation) to EntityBase
//

#ifndef STATEFULENTITYBASE_H
#define STATEFULENTITYBASE_H

#include "EntityBase.h"

template<typename State>
class SEntityBase : public EntityBase {
public:
	SEntityBase(ID id, State s) : EntityBase{id}, state_{s} {}
	State state() const { return state_; }
protected:
	void become(State new_state) { state_ = new_state; }
protected:
	State state_;
};

#endif
