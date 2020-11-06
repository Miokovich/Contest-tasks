#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>



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

	virtual size_t get_vertex_deg(vertex vertex) const = 0;
};



class graph_adj_list_weight : public Graph {
private:
	std::vector<std::vector<std::pair<vertex, vertex>>> adj_list_;

public:
	graph_adj_list_weight(size_t vertex_count, bool is_directed) :
	    Graph(vertex_count, is_directed), adj_list_(vertex_count + 1) {}

	void add_edge(vertex start, vertex finish, long long weight) {
		adj_list_[start].push_back({finish, weight});
		if (!is_directed) {
			adj_list_[finish].push_back({start, weight});
		}
		edge_count++;
	}

	size_t get_vertex_deg(vertex vertex) const {
		return adj_list_[vertex].size();
	}

	std::vector<std::vector<std::pair<vertex, vertex>>> get_adjList() const {
		return adj_list_;
	}

	std::vector<std::pair<vertex, vertex>> get_neighbors(vertex vertex) const {
		return adj_list_[vertex];
	}
};

void find_MST(const graph_adj_list_weight &graph, int &answer) {
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> next_vert;
    std::vector<int> used(graph.get_vertex_count() + 1, 0);
    
    next_vert.push({0, 1}); //weight, num
    answer = 0;

    while (!next_vert.empty()) {
        int curr_vert = next_vert.top().second;
        int curr_dist = next_vert.top().first;
        next_vert.pop();
        if (used[curr_vert]) continue;
        used[curr_vert] = 1;
        answer += curr_dist;
        auto neighbors = graph.get_neighbors(curr_vert);
        for (auto i : neighbors) {
            if (!used[i.first]) {
                next_vert.push({i.second, i.first});
            }
        }
    }
}


int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    size_t n, m;
    std::cin >> n >> m;

    graph_adj_list_weight list_edg(n, false);

    for (size_t i = 0; i < m; ++i){
        size_t from, to;
        long long len;
        std::cin >> from >> to >> len;
        list_edg.add_edge(from, to, len);
    }
    int answer = 0;
    
    find_MST(list_edg, answer);
    std::cout << answer;
    return 0;
}
