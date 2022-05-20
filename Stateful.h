//
// Stateful
// adds custom state (+ operation) to Base
//

#ifndef STATEFUL_H
#define STATEFUL_H

template<typename State>
class Stateful {
public:
	Stateful(State s) : state_{s} {}
	State state() const { return state_; }
protected:
	void become(State new_state) { state_ = new_state; }
protected:
	State state_;
};

#endif
