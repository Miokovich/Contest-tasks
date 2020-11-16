#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <queue>


const int NOT_PROCESSED = -1;


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
		if (!is_directed) {
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


void build_shortest_path_by_prev_links(const std::vector<int> &vertex_parent, const Graph::vertex& current_vertex, 
                                       std::list<Graph::vertex> &shortest_path){
    if (current_vertex != -1) {
        build_shortest_path_by_prev_links(vertex_parent, vertex_parent[current_vertex], shortest_path);
        shortest_path.push_back(current_vertex);
    }

}


std::list<size_t> min_path(const Graph &graph, const Graph::vertex& index_start,
           const Graph::vertex &finish) {

    std::queue<Graph::vertex> que;
    Graph::vertex size_vert = graph.get_vertex_count();
    std::vector<int> dist(size_vert + 1, NOT_PROCESSED), parent(size_vert + 1, NOT_PROCESSED);

    que.push(index_start);
    dist[index_start] = 0;

    while (!que.empty()) {
        Graph::vertex cur_ind = que.front();
        que.pop();
        std::vector<Graph::vertex> neigh = graph.get_neighbors(cur_ind);
        for (auto elem : neigh) {
            if (dist[elem] == NOT_PROCESSED) {
                dist[elem] = dist[cur_ind] + 1;
                parent[elem] = cur_ind;
                que.push(elem);
            }
        }
    }

    std::list<Graph::vertex> path;
    if (dist[finish] == NOT_PROCESSED) return path;
    build_shortest_path_by_prev_links(parent, finish, path);
    return path;
}


int main(){
    size_t vertex, edges;
    size_t start, finish;
    std::cin >> vertex >> edges;
    std::cin >> start >> finish;
    graph_adj_list list_edg(vertex, false);
    
    for (size_t i = 0; i < edges; ++i){
        size_t a, b;
        std::cin >> a >> b;
        list_edg.add_edge(a, b);
    }

    auto answer = min_path(list_edg, start, finish);
    if (answer.size() == 0) {
        std::cout << "-1";
        return 0;
    }
    std::cout << answer.size() - 1<< '\n';
    for (auto elem : answer) {
        std::cout << elem << ' ';
    }
    return 0;
}
