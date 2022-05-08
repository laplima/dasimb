#include "Entity.h"
#include <iostream>

using namespace std;

void Entity::spontaneously()
{
	become(State::INITIATOR);
	cout << id() << ": INITIATOR" << endl;
	become(State::OK);
	send("I", N());
}

void Entity::receiving(EntityBase* origin, const Message& m)
{
	switch (state()) {
		using enum State;
		case IDLE:
			cout << id() << ": received " << m << " from "
				<< origin->id() << endl;
			become(State::OK);
			send(m, N() - origin);
			break;
		default:
			break;
	}
}

void Entity::when()
{
}
