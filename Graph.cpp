#include "Graph.h"
#include <algorithm>
#include <sstream>
#include <queue>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
#include <stdexcept>
#include <string>
#include <set>
#include "RandInt.h"

using std::cout;
using std::endl;
using std::flush;
using std::runtime_error;
using std::string;

Graph::Graph(Size N)
	: N{N}, adjl{static_cast<std::vector<int>::size_type>(N)}
{
}

void Graph::clear_edges()
{
	M = 0;
	for (auto& l : adjl)
		l.clear();
	is_tc_uptodate = false;
}

bool Graph::join(Vertex a, Vertex b, bool rearrange)
{
	if (is_valid(a,b)) {
		if (not adjl[a].contains({b,false})) {		// repeated?
			++M;
			adjl[a].insert(Neighbor{b,rearrange});
			adjl[b].insert(Neighbor{a,rearrange});
			is_tc_uptodate = false;
			return true;
		}
	}
	return false;
}

void Graph::remv(Vertex a, Vertex b)
{
	if (is_valid(a,b)) {
		if (adjl[a].contains(b)) {
			--M;
			adjl[a].erase(b);
			adjl[b].erase(a);
			is_tc_uptodate = false;
		}
	}
}

Graph::Edge Graph::get_rnd_non_rearranged_edge() const
{
	Vertex startv = RandInt{0,N-1}();
	Vertex s = startv;
	auto t = adjl[s].begin();
	while (t->rearranged) {
		++t;
		if (t == adjl[s].end()) {
			s = (s + 1) % N;
			if (s == startv)
				throw std::runtime_error{"no more edges"};
			t = adjl[s].begin();
		}
	}
	return {s, t->id};
}

bool Graph::adjacent(Vertex a, Vertex b) const
{
	if (is_valid(a,b))
		return (adjl[a].contains({b}));
	return false;
}

std::string Graph::to_string(bool mat) const
{
	std::ostringstream ss;
	if (mat) {
		// print as adj matrix
		for (int i=0; i<N; ++i) {
			for (int j=0; j<N; ++j)
				ss << (adjacent(i,j));
			ss << '\n';
		}
	} else {
		int i = 0;
		for (const auto& l : adjl) {
			ss << i++ << ": ";
			for (const Neighbor& v : l)
				ss << v.id << (v.rearranged ? string{"_"} : string{}) << " ";
			ss << '\n';
		}
	}
	return ss.str();
}

bool Graph::is_valid(Vertex a) const
{
	return (a>=0 and a<N);
}

bool Graph::is_valid(Vertex a, Vertex b) const
{
	return is_valid(a) and is_valid(b);
}

std::vector<std::vector<bool>> Graph::matrix() const
{
	std::vector<std::vector<bool>> adj;
	for (int i=0; i<N; ++i) {
		adj.emplace_back();
		for (int j=0; j<N; ++j)
			adj[i].push_back(adjacent(i,j));
	}
	return adj;
}

void Graph::make_spanning_bfs(Vertex v0)
{
	if (!is_valid(v0))
		throw std::out_of_range{"invalid v0"};

	enum class State { white, gray, black };

	std::vector<Vertex> parent(N);
	std::vector<State> state(N,State::white);
	std::queue<Vertex> f;

	state[v0] = State::gray;

	f.push(v0);
	parent[v0] = -1;	// root: no parent

	auto remove = [](decltype(f)& q) { int x = q.front(); q.pop(); return x; };

	while (!f.empty()) {
		int u = remove(f);

		// identify children
		for (const Neighbor& v : adjl[u]) {
			if (state[v.id] == State::white) {
				state[v.id] = State::gray;
				parent[v.id] = u;
				f.push(v.id);
			}
		}
		state[u] = State::black;
	}

	clear_edges();

	for (Vertex v = 0; v<size(); ++v)
		if (is_valid(parent[v]))
			join(v,parent[v]);

	is_tc_uptodate = false;
}

void Graph::add_random_egdes(Size k)
{
	// find incomplete vertices
	std::set<Vertex> incomplete;
	for (Vertex v=0; v<N; ++v)
		if (neighbors_of(v).size() < k)
			incomplete.insert(v);

	RandInt ri{0,1};
	while (incomplete.size() > 1) {
		Vertex a = (ri() == 0) ? *(incomplete.begin()) : *(incomplete.rbegin());
		incomplete.extract(a);
		Vertex b = (ri() == 0) ? *incomplete.begin() : *incomplete.rbegin();
		incomplete.extract(b);
		join(a,b);
		if (neighbors_of(a).size()<k)
			incomplete.insert(a);
		if (neighbors_of(b).size()<k)
			incomplete.insert(b);
	}
	is_tc_uptodate = false;
}

std::vector<std::vector<bool>> Graph::tclosure()
{
	if (not is_tc_uptodate) {
		tc_ = matrix();
		for (int k=0; k<size(); ++k)
			for (int i=0; i<size(); ++i)
				for (int j=0; j<size(); ++j)
					if (tc_[i][k] and tc_[k][j])
						tc_[i][j] = true;
		is_tc_uptodate = true;
	}

	return tc_;
}

bool Graph::connected()
{
	tc_ = tclosure();
	for (const auto& line : tc_)
		for (bool a : line)
			if (not a)
				return false;
	return true;
}

double Graph::C(Vertex i) const
{
	auto ni = neighbors_of(i).size();
	if (ni == 1)
		return 1.0;		// is this right?
	Size count = 0;
	auto& neighs = adjl.at(i);
	for (const auto& a : neighs)
		for (const auto& b : neighs)
			if (adjacent(a,b))
				++count;
	return count/static_cast<double>(ni*(ni-1));
}

double Graph::C() const
{
	double sum = 0.0;
	for (int i=0; i<N; ++i)
		sum += C(i);
	return sum/N;
}

int Graph::dijkstra(Vertex s, Vertex t, std::vector<Vertex>& path)
{
	auto infinity = std::numeric_limits<int>::max();
	std::vector<bool> computed(N,false);
	std::vector<int> Weight(N,infinity);

	Weight[s] = 0.0;
	computed[s] = true;

	Vertex current = s;
	Vertex k{};

	auto w = [this,infinity](Vertex a, Vertex b) {
		return (this->adjacent(a,b)) ? 1 : infinity;
	};

	std::vector<Vertex> precede(N);
	while (current != t) {
		int shortest = infinity;
		int dc = Weight[current];
		for (int i=0; i<N; ++i) {
			if (!computed[i]) {
				int new_Weight = (dc == infinity) ? infinity : dc + w(current,i);
				if (new_Weight < Weight[i]) {
					Weight[i] = new_Weight;
					precede[i] = current;
				}
				if (Weight[i] < shortest) {
					shortest = Weight[i];
					k = i;
				}
			}
		}
		current = k;
		computed[current] = true;
	}

	path.clear();
	current = t;
	while (current != s) {
		path.insert(path.begin(),current);
		current = precede[current];
	}
	path.insert(path.begin(), s);
	return Weight[t];
}

void make_regular_watts(Graph& g, int k)
{
	auto next = [&g](int i, int d) { return (i+d) % g.size(); };

	g.clear_edges();
	for (int i=0; i<g.size(); ++i)
		for (int j=1; j<=k/2; ++j)
			g.join(i,next(i,j));
}

void randomize_edge(Graph& g)
{
	if (not g.connected())
		throw runtime_error{"Graph must be initially connected!\n"};

	auto e = g.get_rnd_non_rearranged_edge();

	g.remv(e);

	RandInt ri{0,g.size()-1};
	Graph::Edge new_edge{e.first,ri()};

	// avoid self-edges
	while (new_edge.second == new_edge.first or new_edge == e)
		new_edge.second = ri();
	while (not g.join(new_edge, true)) {	// rearrange
		new_edge.second = ri();
		while (new_edge.second == new_edge.first or new_edge == e)
			new_edge.second = ri();
	}

	// check properties
	if (g.neighbors_of(e.second).size() < 2)	// no less than 2 edges
		g.join(e,true);		// undo removal + mark edge rearranged

}

void make_connected_smallworld(Graph& g, int k, float p)
{
	make_regular_watts(g,k);

	auto rm = static_cast<Graph::Size>(p * static_cast<float>(g.edges()));
	for (Graph::Size i=0; i<rm; ++i)
		randomize_edge(g);
}

void spanning_tree(Graph& g)
{
	g.make_spanning_bfs(0);
}
