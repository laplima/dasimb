#include "Topology.h"
#include "Graph.h"
#include <stdexcept>

Topology::Topology(int n, int k, float p)
{
	// create n entities
	for (int i=1; i<=n; ++i)
		ents.emplace_back(i);
	small_world(k,p);
}

Entity* Topology::operator[](int id)
{
	return &(ents.at(id2i(id)));
}

void Topology::small_world(int k, float p)
{
	Graph g{static_cast<Graph::Size>(ents.size())};
	make_connected_smallworld(g,k,p);
	spanning_tree(g);
	g.add_random_egdes(2);

	for (int i=0; i<ents.size(); ++i)
		for (int j=0; j<=i; ++j)				// links will be bidrectional
			if (g.adjacent(i,j))
				ents[i].add_neighbor(&ents[j]);	// BL
}

std::ostream& operator<<(std::ostream& os, const Topology& t)
{
	for (const auto& e : t.ents)
		for (const auto* n : e.N())
			os << e.id() << " <-> " << n->id() << std::endl;
	return os;
}
