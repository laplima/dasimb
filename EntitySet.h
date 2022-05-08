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

	// iterator class
	class iterator {
		friend class EntitySet;
	private:
		explicit iterator(typename Neighborhood::iterator i) : it(i) {}
	public:
		iterator& operator++() { ++it; return *this; }
		iterator operator++(int) { it++; return *this; }
		bool operator==(const iterator& i) const { return (i.it == it); }
		bool operator!=(const iterator& i) const { return (i.it != it); }
		EntityBase* operator*() const { return *it; }
	private:
		typename Neighborhood::iterator it;
	};

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
	iterator begin();
	[[nodiscard]] iterator begin() const;
	iterator end();
	[[nodiscard]] iterator end() const;

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
