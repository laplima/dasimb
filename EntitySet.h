//
// (C) 2016-22 Luiz A. de P. Lima Jr.
// All rights reserved.
//
// An EntitySet keeps a list of EntityBasePtr elements,
// especially with operations for insertion (<<) and removal
// (>>) of elements.
//

#ifndef ENTITY_SET_H
#define ENTITY_SET_H

#include <set>
#include <iostream>
#include <initializer_list>
#include <exception>

class EntityBase;
using EntityBasePtr = EntityBase*;
using Neighborhood = std::set<EntityBasePtr>;

class EntitySet {
public:

	EntitySet() = default;
	EntitySet(const EntitySet& es);
	EntitySet(std::initializer_list<EntityBasePtr> lst);
	EntitySet& operator=(const EntitySet& es);
	void clear();
	[[nodiscard]] size_t size() const;
	[[nodiscard]] size_t count(EntityBasePtr e) const;
	[[nodiscard]] bool contains(EntityBasePtr e) const;
	[[nodiscard]] bool empty() const;

	auto begin() { return nset.begin(); }
	[[nodiscard]] auto begin() const { return nset.begin(); }
	auto end() { return nset.end(); }
	[[nodiscard]] auto end() const { return nset.end(); }

	// operators
	EntitySet& operator<<(const EntityBasePtr t);	// insert
	EntitySet& operator>>(EntityBasePtr& e);		// extract
	// concatenate
	EntitySet operator+(const EntitySet& other) const;
	EntitySet& operator+=(const EntitySet& other);
	// subtract
	EntitySet operator-(const EntitySet& other) const;
	EntitySet operator-(const EntityBasePtr& e) const;
	void erase(const EntityBasePtr& e);
	EntitySet& operator-=(const EntitySet& other);
	friend std::ostream& operator<<(std::ostream& os, const EntitySet& s);

protected:
	Neighborhood nset;
};

#endif
