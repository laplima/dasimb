//
// A Graph as an Adjacency List (undirected, unweighted graph)
//

#ifndef GRAPHADJL_H
#define GRAPHADJL_H

#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <utility>
#include <functional>

class Graph {
public:
	using Vertex = int;
	using Size = Vertex;
	using Edge = std::pair<Vertex,Vertex>;
public:
	explicit Graph(Size N);
	[[nodiscard]] Size size() const { return N; }
	[[nodiscard]] Size edges() const { return M; }
	[[nodiscard]] const auto& neighbors_of(Vertex v) const { return adjl.at(v); }
	void clear_edges();
	bool join(Vertex a, Vertex b, bool rearrange=false);
	bool join(const Edge& p, bool rearrange=false) {
		return join(p.first,p.second,rearrange); }
	void remv(Vertex a, Vertex b);
	void remv(const Edge& p) { remv(p.first, p.second); }

	[[nodiscard]] bool adjacent(Vertex a, Vertex b) const;

	[[nodiscard]] Edge get_rnd_non_rearranged_edge() const;
	void make_spanning_bfs(Vertex v0);
	void add_random_egdes(Size k);
	[[nodiscard]] std::vector<std::vector<bool>> matrix() const;
	[[nodiscard]] std::vector<std::vector<bool>> tclosure();
	[[nodiscard]] bool connected();
	[[nodiscard]] std::string to_string(bool mat=false) const;
	int dijkstra(Vertex s, Vertex t, std::vector<Vertex>& path);
	[[nodiscard]] double C(Vertex i) const;		// node clustering coefficient
	[[nodiscard]] double C() const;				// graph's clustering coefficient
private:
	struct Neighbor {
		Vertex id = 0;
		bool rearranged = false;
		Neighbor() = default;
		Neighbor(Vertex v) : id{v} {}
		Neighbor(Vertex v, bool r) : id{v}, rearranged{r} {}
		operator Vertex() const { return id; }
		operator Vertex&() { return id; }
	};
	Size N;		// # of vertices
	Size M = 0;	// # of edges
	std::vector<std::set<Neighbor>> adjl;
	[[nodiscard]] bool is_valid(Vertex a, Vertex b) const;
	[[nodiscard]] bool is_valid(Vertex a) const;
	std::vector<std::vector<bool>> tc_;		// previous computed transitive closure
	bool is_tc_uptodate = false;
};

void make_connected_smallworld(Graph& g, int k, float p);
void make_regular_watts(Graph& g, int k);
void randomize_edge(Graph& g);	// makes sure that the graph remains connected
void spanning_tree(Graph& g);

#endif
