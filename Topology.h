#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <iostream>
#include <vector>
#include <filesystem>
#include "Entity.h"

class Topology {
public:
	explicit Topology(const std::filesystem::path& arq); // topolofy from file
	Topology(int n, int k, float p = 0.0);		// random small world topology
	Entity* operator[](int id);
	[[nodiscard]] int size() const { return static_cast<int>(ents.size()); }

	friend std::ostream& operator<<(std::ostream& os, const Topology& t);
protected:
	[[nodiscard]] int next(int i, int step) const { return (i+step) % size(); }
	[[nodiscard]] int id2i(int id) const { return (id-1); }
	void small_world(int k, float p);
protected:
	std::vector<Entity> ents;
};

#endif
