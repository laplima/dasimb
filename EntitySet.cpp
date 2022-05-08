#include "EntitySet.h"

EntitySet::EntitySet(const EntitySet& es)
{
	*this = es;
}

EntitySet::EntitySet(std::initializer_list<EntityBasePtr> lst)
	: nset (lst)
{
}

EntitySet& EntitySet::operator=(const EntitySet& es)
{
	if (this != &es)
		nset = es.nset;
	return *this;
}

void EntitySet::clear()
{
	nset.clear();
}

size_t EntitySet::size() const
{
	return nset.size();
}

size_t EntitySet::count(EntityBasePtr e) const
{
	return nset.count(e);
}

bool EntitySet::contains(EntityBasePtr e) const
{
	return nset.contains(e);
}

bool EntitySet::empty() const
{
	return (size() == 0);
}

EntitySet::iterator EntitySet::begin()
{
	return iterator{ nset.begin() };
}

EntitySet::iterator EntitySet::begin() const
{
	return iterator{ nset.begin() };
}

EntitySet::iterator EntitySet::end()
{
	return iterator{ nset.end()};
}

EntitySet::iterator EntitySet::end() const
{
	return iterator{ nset.end()};
}

// insert
EntitySet& EntitySet::operator<<(const EntityBasePtr t)
{
	nset.insert(t);
	return *this;
}

// extract
EntitySet& EntitySet::operator>>(EntityBasePtr& e)
{
	if (empty()) throw std::out_of_range("EntitySet::empty");
	e = *nset.begin();
	nset.erase(nset.begin());
	return *this;
}

// concatenate
EntitySet EntitySet::operator+(const EntitySet& other) const
{
	EntitySet res{*this};
	for (const auto x : other)
		res << x;
	return res;
}

EntitySet& EntitySet::operator+=(const EntitySet& other)
{
	for (auto x : other)
		*this << x;
	return *this;
}

// subtract
EntitySet EntitySet::operator-(const EntitySet& other) const
{
	EntitySet res{*this};
	for (const auto x : other)
		res.erase(x);
	return res;
}

EntitySet EntitySet::operator-(const EntityBasePtr& e) const
{
	EntitySet res{*this};
	res.erase(e);
	return res;
}

void EntitySet::erase(const EntityBasePtr& e)
{
	nset.erase(e);
}

EntitySet& EntitySet::operator-=(const EntitySet& other)
{
	for (auto x : other)
		this->erase(x);
	return *this;
}

std::ostream& operator<<(std::ostream& os, const EntitySet& s)
{
	for (auto x : s.nset)
		os << x << " ";
	return os;
}
