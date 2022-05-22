#include "Entity.h"
#include <iostream>

using namespace std;

Entity::Entity(ID id) : StatefulEntity{id, State::IDLE}
{
}

void Entity::spontaneously()
{
	// Traversal
	become(State::INITIATOR);
	unvisited = Nx();
	initiator = true;
	visits();
}

void Entity::receiving(EntityBase* origin, const Message& m)
{
	cout << "    " << id() << " received " << m << endl;
	switch (state()) {
		using enum State;
		case IDLE:
			if (m == "T") {
				entry = origin;
				unvisited = Nx() - origin;
				initiator = false;
				visits();
			}
			break;
		case VISITED:
			if (m == "T") {
				unvisited.erase(origin);
				cout << id() << " sending B to " << origin->id() << endl;
				send("B", { origin });
			} else if (m == "R" or m == "B") {
				visits();
			}
			break;
		default:
			// do nothing
			break;
	}
}

void Entity::when()
{
}

void Entity::visits()
{
	if (not unvisited.empty()) {
		EntityBase* next = nullptr;
		unvisited >> next;
		become(State::VISITED);
		cout << id() << " sending T to " << next->id() << endl;
		send("T", {next} );
	} else {
		become(State::OK);
		if (not initiator) {
			cout << id() << " sending R to " << entry->id() << endl;
			send("R", {entry});
		}
	}
}
