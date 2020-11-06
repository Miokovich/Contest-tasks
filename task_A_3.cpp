#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <algorithm>


class Graph {
protected:
	size_t vertex_count, edge_count;
	bool is_directed;

public:
	typedef size_t vertex;
	Graph(size_t vertex_count, bool is_directed) :
	    vertex_count(vertex_count), is_directed(is_directed), edge_count(0) {}

	size_t get_vertex_count() const {
		return vertex_count;
	}

	size_t get_edge_count() const {
		if (is_directed == 0) {
			return edge_count / 2;
		}
		return edge_count;
	}

	bool get_direction() const {
		return is_directed;
	}

	virtual void add_edge(const vertex& start, const vertex& finish) = 0;
	virtual size_t get_vertex_deg(const vertex& vertex) const = 0;
	virtual std::vector<std::vector<vertex>> get_adjList() const = 0;
	virtual std::vector<vertex> get_neighbors(const vertex& v) const = 0;
};


class graph_adj_list : public Graph {
private:
	std::vector<std::vector<vertex>> adj_list_;

public:
	graph_adj_list(size_t vertex_count, bool is_directed) : Graph(vertex_count, is_directed), adj_list_(vertex_count + 1) {}

	void add_edge(const vertex& start, const vertex& finish) override {
		adj_list_[start].push_back(finish);
		if (!is_directed) {
			adj_list_[finish].push_back(start);
		}
		edge_count++;
	}

	size_t get_vertex_deg(const vertex& vertex) const override {
		return adj_list_[vertex].size();
	}

	std::vector<std::vector<vertex>> get_adjList() const override {
		return adj_list_;
	}

	std::vector<vertex> get_neighbors(const vertex& vertex) const override {
		return adj_list_[vertex];
	}
};

void DFS_visit(const Graph &graph, std::vector<char> &color,
               int start, bool is_root, size_t time,
               std::set<int> &answer, std::vector<int> &t_in, std::vector<int> &t_up) {
    color[start] = 'g';
    size_t children = 0;
    ++time;
    t_in[start] = time;
    t_up[start] = time;
    auto neighbors = graph.get_neighbors(start);
    for (const auto &neigh : neighbors){
        if (color[neigh] != 'w'){
            t_up[start] = std::min(t_up[start], t_in[neigh]);
        }
        if (color[neigh] == 'w'){
            DFS_visit(graph, color, neigh, false, time, answer, t_in, t_up);
            ++children;
            t_up[start] = std::min(t_up[start], t_up[neigh]);
            if (t_in[start] <= t_up[neigh] && !is_root) {
                answer.insert(start);
            }
        }
    }
    if (is_root && children >= 2) {
        answer.insert(start);
    }
    color[start] = 'b';
}


std::set<int> cut_vertices(const Graph &graph) {
    std::set<int> vertices;
    std::vector<char> color(graph.get_vertex_count() + 1, 'w');
    size_t time = 0;
    for (size_t i = 1; i < graph.get_vertex_count() + 1; ++i) {
        if (color[i] == 'w') {
            std::vector<int> t_in(graph.get_vertex_count() + 1), t_out(graph.get_vertex_count() + 1);
            DFS_visit(graph, color, i, true, time, vertices, t_in, t_out);
        }
    }
    return vertices;
}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    size_t vertex, edges;
    std::cin >> vertex >> edges;

    graph_adj_list list_edg(vertex, false);

    for (size_t i = 0; i < edges; ++i){
        size_t from, to;
        std::cin >> from >> to;
        list_edg.add_edge(from, to);
    }

    std::set<int> answer = cut_vertices(list_edg);
    std::cout << answer.size() << '\n';
    for (auto i : answer) {
        std::cout << i << '\n';
    }
    return 0;
}
